package main

// #include <stdlib.h>
// typedef void (*cb)(char*);
// static void callback(cb f, char* message) { f(message); }
import "C"
import (
	"context"
	"net/url"
	"unsafe"

	"spiderden.org/murse"
	"spiderden.org/murse/htvn"
)

func main() {}

const (
	OP_NONE = iota
	OP_UPGRADE
	OP_VERIFY
	OP_REPAIR
)

//export murseop
func murseop(operation C.int, dl_url *C.char, game_dir *C.char, key *C.char, callback C.cb) C.int {
	gdl_url := C.GoString(dl_url)
	ggame_dir := C.GoString(game_dir)
	tvn_url, err := url.Parse(gdl_url)
	if err != nil {
		return -1
	}
	htvnfs := htvn.NewFS(tvn_url)
	channel := make(chan murse.Entry)
	done := make(chan error)
	switch operation {
	case OP_NONE:
		return -1
	case OP_REPAIR:
		fallthrough
	case OP_VERIFY:
		{
			verify := murse.VerifyArgs{
				Dir:        ggame_dir,
				TVNFS:      htvnfs,
				HTTP1:      false,
				OWGameInfo: true,
				Dry:        false,
				Repair:     operation == OP_REPAIR,
				KeyR:       nil,
			}
			v_op := murse.NewVerifyOperation(verify)
			go func() {
				err := v_op.Start(channel, context.Background())
				done <- err
			}()
		}
	case OP_UPGRADE:
		{
			upgrade := murse.UpgradeArgs{
				Dir:              ggame_dir,
				TVNFS:            htvnfs,
				Threads:          4,
				OWGameInfo:       true,
				Dry:              false,
				KeyR:             nil,
				DisableStreaming: true,
			}
			u_op := murse.NewUpgradeOperation(upgrade)
			go func() {
				err := u_op.Start(channel, context.Background())
				done <- err
			}()
		}
	}
	for {
		select {
		case msg := <-channel:
			{
				str := C.CString(msg.MurseFmt())
				C.callback(callback, str)
				C.free(unsafe.Pointer(str))
			}
		case err := <-done:
			{
				if err == nil {
					return 0
				} else {
					estr := C.CString(err.Error())
					C.callback(callback, estr)
					C.free(unsafe.Pointer(estr))
					return -1
				}
			}
		}
	}
}
