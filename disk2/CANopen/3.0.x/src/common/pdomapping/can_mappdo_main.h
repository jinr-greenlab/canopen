#if CAN_NOF_PDO_RECEIVE > 0
	#include "__map_recv_001_032.h"
#endif
#if CAN_NOF_PDO_RECEIVE > 32
	#include "__map_recv_033_064.h"
#endif
#if CAN_NOF_PDO_RECEIVE > 64
	#include "__map_recv_065_096.h"
#endif
#if CAN_NOF_PDO_RECEIVE > 96
	#include "__map_recv_097_128.h"
#endif
#if CAN_NOF_PDO_RECEIVE > 128
	#include "__map_recv_129_160.h"
#endif
#if CAN_NOF_PDO_RECEIVE > 160
	#include "__map_recv_161_192.h"
#endif
#if CAN_NOF_PDO_RECEIVE > 192
	#include "__map_recv_193_224.h"
#endif
#if CAN_NOF_PDO_RECEIVE > 224
	#include "__map_recv_225_256.h"
#endif
#if CAN_NOF_PDO_RECEIVE > 256
	#include "__map_recv_257_288.h"
#endif
#if CAN_NOF_PDO_RECEIVE > 288
	#include "__map_recv_289_320.h"
#endif
#if CAN_NOF_PDO_RECEIVE > 320
	#include "__map_recv_321_352.h"
#endif
#if CAN_NOF_PDO_RECEIVE > 352
	#include "__map_recv_353_384.h"
#endif
#if CAN_NOF_PDO_RECEIVE > 384
	#include "__map_recv_385_416.h"
#endif
#if CAN_NOF_PDO_RECEIVE > 416
	#include "__map_recv_417_448.h"
#endif
#if CAN_NOF_PDO_RECEIVE > 448
	#include "__map_recv_449_480.h"
#endif
#if CAN_NOF_PDO_RECEIVE > 480
	#include "__map_recv_481_512.h"
#endif

#if CAN_NOF_PDO_TRANSMIT > 0
	#include "__map_tran_001_032.h"
#endif
#if CAN_NOF_PDO_TRANSMIT > 32
	#include "__map_tran_033_064.h"
#endif
#if CAN_NOF_PDO_TRANSMIT > 64
	#include "__map_tran_065_096.h"
#endif
#if CAN_NOF_PDO_TRANSMIT > 96
	#include "__map_tran_097_128.h"
#endif
#if CAN_NOF_PDO_TRANSMIT > 128
	#include "__map_tran_129_160.h"
#endif
#if CAN_NOF_PDO_TRANSMIT > 160
	#include "__map_tran_161_192.h"
#endif
#if CAN_NOF_PDO_TRANSMIT > 192
	#include "__map_tran_193_224.h"
#endif
#if CAN_NOF_PDO_TRANSMIT > 224
	#include "__map_tran_225_256.h"
#endif
#if CAN_NOF_PDO_TRANSMIT > 256
	#include "__map_tran_257_288.h"
#endif
#if CAN_NOF_PDO_TRANSMIT > 288
	#include "__map_tran_289_320.h"
#endif
#if CAN_NOF_PDO_TRANSMIT > 320
	#include "__map_tran_321_352.h"
#endif
#if CAN_NOF_PDO_TRANSMIT > 352
	#include "__map_tran_353_384.h"
#endif
#if CAN_NOF_PDO_TRANSMIT > 384
	#include "__map_tran_385_416.h"
#endif
#if CAN_NOF_PDO_TRANSMIT > 416
	#include "__map_tran_417_448.h"
#endif
#if CAN_NOF_PDO_TRANSMIT > 448
	#include "__map_tran_449_480.h"
#endif
#if CAN_NOF_PDO_TRANSMIT > 480
	#include "__map_tran_481_512.h"
#endif

static void define_pdo_map(void)
{
#if CAN_NOF_PDO_RECEIVE > 0
	define_map_recv_001_032();
#endif
#if CAN_NOF_PDO_RECEIVE > 32
	define_map_recv_033_064();
#endif
#if CAN_NOF_PDO_RECEIVE > 64
	define_map_recv_065_096();
#endif
#if CAN_NOF_PDO_RECEIVE > 96
	define_map_recv_097_128();
#endif
#if CAN_NOF_PDO_RECEIVE > 128
	define_map_recv_129_160();
#endif
#if CAN_NOF_PDO_RECEIVE > 160
	define_map_recv_161_192();
#endif
#if CAN_NOF_PDO_RECEIVE > 192
	define_map_recv_193_224();
#endif
#if CAN_NOF_PDO_RECEIVE > 224
	define_map_recv_225_256();
#endif
#if CAN_NOF_PDO_RECEIVE > 256
	define_map_recv_257_288();
#endif
#if CAN_NOF_PDO_RECEIVE > 288
	define_map_recv_289_320();
#endif
#if CAN_NOF_PDO_RECEIVE > 320
	define_map_recv_321_352();
#endif
#if CAN_NOF_PDO_RECEIVE > 352
	define_map_recv_353_384();
#endif
#if CAN_NOF_PDO_RECEIVE > 384
	define_map_recv_385_416();
#endif
#if CAN_NOF_PDO_RECEIVE > 416
	define_map_recv_417_448();
#endif
#if CAN_NOF_PDO_RECEIVE > 448
	define_map_recv_449_480();
#endif
#if CAN_NOF_PDO_RECEIVE > 480
	define_map_recv_481_512();
#endif

#if CAN_NOF_PDO_TRANSMIT > 0
	define_map_tran_001_032();
#endif
#if CAN_NOF_PDO_TRANSMIT > 32
	define_map_tran_033_064();
#endif
#if CAN_NOF_PDO_TRANSMIT > 64
	define_map_tran_065_096();
#endif
#if CAN_NOF_PDO_TRANSMIT > 96
	define_map_tran_097_128();
#endif
#if CAN_NOF_PDO_TRANSMIT > 128
	define_map_tran_129_160();
#endif
#if CAN_NOF_PDO_TRANSMIT > 160
	define_map_tran_161_192();
#endif
#if CAN_NOF_PDO_TRANSMIT > 192
	define_map_tran_193_224();
#endif
#if CAN_NOF_PDO_TRANSMIT > 224
	define_map_tran_225_256();
#endif
#if CAN_NOF_PDO_TRANSMIT > 256
	define_map_tran_257_288();
#endif
#if CAN_NOF_PDO_TRANSMIT > 288
	define_map_tran_289_320();
#endif
#if CAN_NOF_PDO_TRANSMIT > 320
	define_map_tran_321_352();
#endif
#if CAN_NOF_PDO_TRANSMIT > 352
	define_map_tran_353_384();
#endif
#if CAN_NOF_PDO_TRANSMIT > 384
	define_map_tran_385_416();
#endif
#if CAN_NOF_PDO_TRANSMIT > 416
	define_map_tran_417_448();
#endif
#if CAN_NOF_PDO_TRANSMIT > 448
	define_map_tran_449_480();
#endif
#if CAN_NOF_PDO_TRANSMIT > 480
	define_map_tran_481_512();
#endif
}
