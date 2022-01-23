#include <DS401_header.h>

#if CHECK_VERSION_APPL(2, 1, 1)
//  CHECK_VERSION_APPL(2, 0, 2)

unsigned32 read_dev_type_object(canindex index, cansubind subind)
{
	unsigned32 devtype;

	if (index == CAN_INDEX_DEVICE_TYPE) {
		devtype = CAN_DEVICE_TYPE;
		if (digital_inblocks != 0) devtype |= (DEVTYPE_MASK_DIGITAL_INPUT | DEVTYPE_MASK_PDO_MAPPING);
		if (digital_outblocks != 0) devtype |= DEVTYPE_MASK_DIGITAL_OUTPUT;
		if (analog_inputs != 0) devtype |= DEVTYPE_MASK_ANALOG_INPUT;
		if (analog_outputs != 0) devtype |= DEVTYPE_MASK_ANALOG_OUTPUT;
		return devtype;
	} else if (index == CAN_INDEX_MAN_STATUS) {
		if (digital_inblocks != 0 || digital_outblocks != 0) return CAN_MAN_STATUS_DIOC;
		if (analog_inputs != 0) return CAN_MAN_STATUS_ANINP;
		if (analog_outputs != 0) return CAN_MAN_STATUS_ANOUT;
	} else if (index == CAN_INDEX_IDENTITY) {
 		if (subind == 0) return 4;
 		if (subind == 1) return CAN_VENDOR_ID;
 		if (subind == 2) return ((unsigned32)project_code << 16) | CAN_PROJECT_CODE_DEVICE_VARIANT;
 		if (subind == 3) return CAN_REV_NUM;
 		if (subind == 4) return get_serial_number();
	}
	return 0;
}

void read_dev_string_object(canindex index, cansubind subind, canbyte *data)
{
	if (index == CAN_INDEX_MAN_DEV_NAME) {
		*data = 'I'; data++;
		*data = 'O'; data++;
		*data = 'r'; data++;
		*data = 'e'; data++;
		*data = 'm'; data++;
		*data = 'o'; data++;
		*data = 't'; data++;
		*data = 'e'; data++;
		*data = ' '; data++;
		*data = 'C'; data++;
		*data = 'i'; data++;
		*data = 'A'; data++;
		*data = '4'; data++;
		*data = '0'; data++;
		*data = '1'; data++;
		*data = '+'; data++;
		*data = ' '; data++;
		*data = 'E'; data++;
		*data = 'N'; data++;
		*data = '5'; data++;
		*data = '0'; data++;
		*data = '3'; data++;
		*data = '2'; data++;
		*data = '5'; data++;
		*data = '-'; data++;
		*data = '5'; data++;
		*data = ' '; data++;
        if (project_code == CAN_PROJECT_CODE_DIOC) {
			*data = 'D'; data++;
			*data = 'I'; data++;
			*data = 'O';
        } else {
			*data = 'A'; data++;
			if (analog_inputs == 0 && analog_outputs == 0) {
				*data = '?';
			}
			if (analog_inputs != 0) {
				*data = 'I'; data++; 
			}
			if (analog_outputs != 0) {
				 *data = 'O';
			}
		}
	} else if (index == CAN_INDEX_MAN_HARD_VER) {
		*data = 'v'; data++;
		*data = 'e'; data++;
		*data = 'r'; data++;
		*data = '_'; data++;
		*data = '0'; data++;
		*data = '5'; data++;
		*data = 'h';
	} else if (index == CAN_INDEX_MAN_SOFT_VER) {
		*data = 'v'; data++;
		*data = 'e'; data++;
		*data = 'r'; data++;
		*data = '_'; data++;
		*data = '2'; data++;
		*data = '.'; data++;
		*data = '1'; data++;
		*data = '.'; data++;
		*data = '0'; data++;
		*data = '-'; data++;
		*data = '3';
	}
}

#endif
