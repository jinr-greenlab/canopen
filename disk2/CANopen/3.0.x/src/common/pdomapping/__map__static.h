	// TEST and sample static PDO mapping below.

	pdomap[0].map[0] = 0x20010108;
	pdomap[0].map[1] = 0x20010520;
	pdomap[0].map[2] = 0x20010210;
	pdomap[0].nrec = 3;
	server_write_obd_u32(CAN_INDEX_RCVPDO_COMM_MIN, 2, 4);
	// First receive PDO mapping.
	// Application object: index 0x2001 sub-index 1 (type unsigned char, 8 bits).
	// Application object: index 0x2001 sub-index 5 (type float, 32 bits).
	// Application object: index 0x2001 sub-index 2 (type short, 16 bits).
	// Number of mapped application objects in PDO is three.
	// The PDO is configured as transferred synchronously and cyclically.

	pdomap[0+CAN_NOF_PDO_RECEIVE].map[0] = 0x20010108;
	pdomap[0+CAN_NOF_PDO_RECEIVE].map[1] = 0x20010520;
	pdomap[0+CAN_NOF_PDO_RECEIVE].map[2] = 0x20010210;
	pdomap[0+CAN_NOF_PDO_RECEIVE].nrec = 3;
	server_write_obd_u32(CAN_INDEX_TRNPDO_COMM_MIN, 2, 4);
	// First transmit PDO mapping.
	// Application object: index 0x2001 sub-index 1 (type unsigned char, 8 bits).
	// Application object: index 0x2001 sub-index 5 (type float, 32 bits).
	// Application object: index 0x2001 sub-index 2 (type short, 16 bits).
	// Number of mapped application objects in PDO is three.
	// Transmission type of the first transmit PDO communication parameter is set.
	// The PDO is configured as transferred synchronously and cyclically.
	// Four SYNCs are necessary to trigger PDO transmissions.

	pdomap[1].map[0] = 0x20010320;
	pdomap[1].nrec = 1;
	server_write_obd_u32(CAN_INDEX_RCVPDO_COMM_MIN+1, 2, 10);
	// Second receive PDO mapping.
	// Application object: index 0x2001 sub-index 3 (type unsigned int, 32 bits).
	// Number of mapped application objects in PDO (one) is written down.
	// The PDO is configured as transferred synchronously and cyclically.

	pdomap[1+CAN_NOF_PDO_RECEIVE].map[0] = 0x20010320;
	pdomap[1+CAN_NOF_PDO_RECEIVE].nrec = 1;
	server_write_obd_u32(CAN_INDEX_TRNPDO_COMM_MIN+1, 2, 10);
	// Second transmit PDO mapping.
	// Application object: index 0x2001 sub-index 3 (type unsigned int, 32 bits).
	// Number of mapped application objects in PDO (one) is written down.
	// Transmission type of the second transmit PDO communication parameter is set.
	// The PDO is configured as transferred synchronously and cyclically.
	// Ten SYNCs are necessary to trigger PDO transmissions.

	pdomap[2].map[0] = 0x20010440;
	pdomap[2].nrec = 1;
	server_write_obd_u32(CAN_INDEX_RCVPDO_COMM_MIN+2, 2, 16);
	// Third receive PDO mapping.
	// Application object: index 0x2001 sub-index 4 (type long long, 64 bits).
	// Number of mapped application objects in PDO (one) is written down.
	// The PDO is configured as transferred synchronously and cyclically.

	pdomap[2+CAN_NOF_PDO_RECEIVE].map[0] = 0x20010440;
	pdomap[2+CAN_NOF_PDO_RECEIVE].nrec = 1;
	server_write_obd_u32(CAN_INDEX_TRNPDO_COMM_MIN+2, 2, 16);
	// Third transmit PDO mapping.
	// Application object: index 0x2001 sub-index 4 (type long long, 64 bits).
	// Number of mapped application objects in PDO (one) is written down.
	// Transmission type of the third transmit PDO communication parameter is set.
	// The PDO is configured as transferred synchronously and cyclically.
	// Sixteen SYNCs are necessary to trigger PDO transmissions.

	pdomap[3].map[0] = 0x20010640;
	pdomap[3].nrec = 1;
	server_write_obd_u32(CAN_INDEX_RCVPDO_COMM_MIN+3, 2, 28);
	// Fourth receive PDO mapping.
	// Application object: index 0x2001 sub-index 6 (type double, 64 bits) is mapped.
	// Number of mapped application objects in PDO (one) is written down.
	// The PDO is configured as transferred synchronously and cyclically.

	pdomap[3+CAN_NOF_PDO_RECEIVE].map[0] = 0x20010640;
	pdomap[3+CAN_NOF_PDO_RECEIVE].nrec = 1;
	server_write_obd_u32(CAN_INDEX_TRNPDO_COMM_MIN+3, 2, 28);
	// Fourth transmit PDO mapping.
	// Application object: index 0x2001 sub-index 6 (type double, 64 bits) is mapped.
	// Number of mapped application objects in PDO (one) is written down.
	// Transmission type of the forth transmit PDO communication parameter is set.
	// The PDO is configured as transferred synchronously and cyclically.
	// Twenty eight SYNCs are necessary to trigger PDO transmissions.
