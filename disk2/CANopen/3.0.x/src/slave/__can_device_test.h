unsigned32 read_dev_type_object(canindex index, cansubind subind)
{
	if (index == CAN_INDEX_DEVICE_TYPE) return CAN_DEVICE_TYPE;
	else if (index == CAN_INDEX_MAN_STATUS) return CAN_MAN_STATUS;
	else if (index == CAN_INDEX_IDENTITY) {
		switch (subind) {
			case 0:	return 4;
			case 1:	return CAN_VENDOR_ID;
			case 2:	return CAN_PROD_CODE;
			case 3:	return CAN_REV_NUM;
			case 4:	return get_serial_number();
		}
	}
	return 0;
}

void read_dev_string_object(canindex index, cansubind subind, canbyte *data)
{
	if (index == CAN_INDEX_MAN_DEV_NAME) {
		*data = 'C'; data++;
		*data = 'A'; data++;
		*data = 'N'; data++;
		*data = 'o'; data++;
		*data = 'p'; data++;
		*data = 'e'; data++;
		*data = 'n'; data++;
		*data = ' '; data++;
		*data = 't'; data++;
		*data = 'e'; data++;
		*data = 's'; data++;
 		*data = 't'; data++;
		*data = ' '; data++;
		*data = 'm'; data++;
		*data = 'o'; data++;
		*data = 'd'; data++;
		*data = 'u'; data++;
		*data = 'l'; data++;
		*data = 'e';
	} else if (index == CAN_INDEX_MAN_HARD_VER) {
		*data = 'v'; data++;
		*data = 'e'; data++;
		*data = 'r'; data++;
		*data = '_'; data++;
		*data = '1'; data++;
		*data = '.'; data++;
		*data = '0'; data++;
		*data = '.'; data++;
		*data = '0';
	} else if (index == CAN_INDEX_MAN_SOFT_VER) {
		*data = 'v'; data++;
		*data = 'e'; data++;
		*data = 'r'; data++;
		*data = '_'; data++;
		*data = '3'; data++;
		*data = '.'; data++;
		*data = '0'; data++;
		*data = '.'; data++;
		*data = '0'; data++;
		*data = '-'; data++;
		*data = '4';
	}
}
