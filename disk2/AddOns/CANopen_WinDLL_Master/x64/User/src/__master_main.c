#include <master_user_header.h>

static int16 fnr;

static void show_logger(void)
{
	struct eventlog ev;

	if (read_logger_event(&ev) == GEN_RETOK) {
		printf("logger  %3i  %3i  %3i  %6i (0x%04X)  %10i (0x%08X)\n",
				ev.node, ev.cls, ev.type, ev.code, (unsigned16)ev.code, ev.info, (unsigned32)ev.info);
	}
}

static void configure_CANopen_slave(cannode node)
{
	unsigned32 data;
	canindex obdind;

	printf("\n");

	nmt_master_command(CAN_NMT_ENTER_PRE_OPERATIONAL, node);	// EN50325-5
	Sleep(50);

	nmt_master_command(CAN_NMT_RESET_NODE, node);
	printf("Resetting node %-1i\n", node);

	Sleep(500);
	
	fnr = write_master_hbt(node, 1200);
	printf("Master heartbeat   ret %-1i\n", fnr);
	data = 1000;
	fnr = write_device_object_sdo(node, 0x1017, 0, (canbyte*)&data, 2);
	printf("Slave heartbeat   ret %-1i\n", fnr);

	fnr = add_node_object_dictionary(node, 0x6000, 1, CAN_DEFTYPE_UNSIGNED8);
	printf("Add digital inputs OBD entry   ret %-1i\n", fnr);

//	Digital outputs will be set from the inputs

	obdind = CAN_INDEX_RCVPDO_MAP_MIN+(node-1)*CAN_NOF_PDO_TRAN_SLAVE;
	// The first master receive PDO (TPDO for the node)
	fnr = write_pdo_mapping(obdind, 0, 0);
	printf("Master receive PDO mapping sub0 disable   ret %-1i\n", fnr);
	fnr = write_pdo_mapping(obdind, 1, 0x60000108);
	printf("Master receive PDO mapping sub1, digital inputs   ret %-1i\n", fnr);
	fnr = write_pdo_mapping(obdind, 0, 1);
	printf("Master receive PDO mapping sub0 enable   ret %-1i\n", fnr);

	obdind = CAN_INDEX_TRNPDO_MAP_MIN+(node-1)*CAN_NOF_PDO_RECV_SLAVE;
	// The first master transmit PDO (RPDO for the node)
	fnr = write_pdo_mapping(obdind, 0, 0);
	printf("Master transmit PDO mapping sub0 disable   ret %-1i\n", fnr);
	fnr = write_pdo_mapping(obdind, 1, 0x60000108);
	printf("Master transmit PDO mapping sub1 digital inputs   ret %-1i\n", fnr);
	fnr = write_pdo_mapping(obdind, 0, 1);
	printf("Master transmit PDO mapping sub0 enable   ret %-1i\n", fnr);

	set_all_pdos_state(VALID);
	printf("Setting all master PDOs to VALID state\n");

	nmt_master_command(CAN_NMT_START_REMOTE_NODE, node);
	printf("Starting node %-1i\n", node);

	printf("\n");
}

static void read_device_objects(cannode node)
{
	unsigned32 data, datasize;
	char dch[100];

	data = 0;
	datasize = 2;
	read_device_object_sdo(node, 0x1017, 0, (canbyte*)&data, &datasize);
	printf("Slave heartbeat: %-1i\n", data);

	printf("\n");
	
	memset(dch, 0, sizeof(dch));
	datasize = sizeof(dch);
	read_device_object_sdo(node, 0x1008, 0, (canbyte*)&dch, &datasize);
	dch[sizeof(dch) - 1] = 0;		// May be NOT ASCIIZ
	printf("Manufacturer Device Name: %s\n", dch);
	printf("Symbols read actually: %-1i\n", datasize);

	printf("\n");
}

static void monitor(void)
{
	transmit_can_pdo(0x1800);	// Digital outputs set from inputs.
	show_logger();
	canopen_monitor();
	Sleep(100);
}

int main(void)
{
  fnr = start_can_master(CAN_NETWORK_CONTROLLER, CAN_BITRATE_INDEX);
	if (fnr != CAN_RETOK) {
		printf("\nMaster NOT started, error %-1i\n", fnr);
		return CAN_ERRET_MAIN;
	}

  configure_CANopen_slave(1);      // node 1
  read_device_objects(1);          // node 1

//  configure_CANopen_slave(127);    // node 127
//	read_device_objects(127);		     // node 127

  while (TRUE) monitor();
	if (stop_can_master() != CAN_RETOK) return CAN_ERRET_MAIN;
	return CAN_RETURN_MAIN;
}
