#include <can_header.h>

#if CHECK_VERSION(3, 0, 1)
//  CHECK_VERSION(2, 3, 1)
//  CHECK_VERSION(2, 2, 1)
//  CHECK_VERSION(2, 1, 2)
//  CHECK_VERSION(2, 0, 1)
//  CHECK_VERSION(1, 7, 1)

#define MASK_PDOMAP_INDEX		0xFFFF0000	// PDO mapping entry index mask
#define MASK_PDOMAP_SUBIND		0x0000FF00	// PDO mapping entry subindex mask
#define MASK_PDOMAP_LENGTH		0x000000FF	// PDO mapping entry object length mask

#define NOF_PDO_MAPPED	(CAN_NOF_PDO_RECEIVE+CAN_NOF_PDO_TRANSMIT)

#if CAN_APPLICATION_MODE == SLAVE && CAN_PDO_MAPPING_MODE == STATIC
	#include "can_pdo_map_static.h"
#else
	#if CAN_DYNAMIC_MAPPING_GRANULARITY	== MAPBIT
		#include "can_pdo_map_dynamic_bit.h"
	#elif CAN_DYNAMIC_MAPPING_GRANULARITY == MAPBYTE
		#include "can_pdo_map_dynamic_byte.h"
	#endif
#endif

#endif
