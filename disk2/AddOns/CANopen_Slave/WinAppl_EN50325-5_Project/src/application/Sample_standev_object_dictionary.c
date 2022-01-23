#include <DS401_header.h>

#if CHECK_VERSION_APPL(2, 1, 0)
//  CHECK_VERSION_APPL(2, 0, 0)
//  CHECK_VERSION_APPL(1, 2, 0)

int32 sample_data[4];	// Массив данных. Создается и поддерживается конечным приложением.
						// Используется в качестве источника данных для объектного словаря CANopen.

const unsigned8 array_size=4;	// Число субиндексов CANopen объекта. Для данного примера равно размеру массива данных.

// Функция определения CANopen объектов.
// Формирует прикладной объектный словарь CANopen на основе существующих прикладных данных.
static void get_object_standev(struct object *obj)
{
	obj->size = CAN_ERRET_OBD_NOSUBIND;
	obj->deftype = 0;
	obj->access = 0;
	obj->pnt = NULL;

	if (obj->index == 0x6100) {		// Индекс объектного словаря, его значение определяется стандартным прикладным профилем
	  								// в диапазоне (0x6000..0x9FFF) 
	                                // или выбирается разработчиком приложения в диапазоне (0x2000..0x5FFF)
	                                // Объекты в диапазоне (0x2000..0x5FFF) обслуживаются аналогично в файле DS401_manspec.c
		if (obj->subind == 0) {						// Субиндекс объектного словаря
			obj->size = sizeof(unsigned8);					// Размер объекта в байтах
			obj->deftype = CAN_DEFTYPE_UNSIGNED8;			// Тип данных объекта
			obj->access = CAN_MASK_ACCESS_RO;			 	// Доступ только по чтению
			obj->pnt = (canbyte*)&array_size;  				// Выдается указатель на число субиндексов.
		} else if (obj->subind <= 4) {				// Субиндексы объектного словаря
			obj->size = sizeof(int32);						// Размер объекта в байтах
			obj->deftype = CAN_DEFTYPE_INTEGER32;			// Тип данных объекта
			obj->access = CAN_MASK_ACCESS_RO | CAN_MASK_ACCESS_PDO;		// Доступ только по чтению и возможность PDO отображения
			obj->pnt = (canbyte*)&sample_data[obj->subind-1];			// Байтовый указатель на объект - источник прикладных данных
		}
		return;
	}

	obj->size = CAN_ERRET_OBD_NOOBJECT;
}

// Функция запроса размера CANopen объекта
// Обслуживает объекты в диапазоне индексов 0x6000..0x9FFF
int32 server_get_standev_objsize(canindex index, cansubind subind)
{
	struct object obj;

	obj.index = index;
	obj.subind = subind;
	get_object_standev(&obj);
	return obj.size;
}

// Функция запроса вида доступа к CANopen объекту
// Обслуживает объекты в диапазоне индексов 0x6000..0x9FFF
int16 server_see_standev_access(canindex index, cansubind subind)
{
	struct object obj;

	obj.index = index;
	obj.subind = subind;
	get_object_standev(&obj);
	if (obj.size <= 0) return (int16)obj.size;
	return obj.access;
}

// Функция запроса типа CANopen объекта
// Обслуживает объекты в диапазоне индексов 0x6000..0x9FFF
int16 server_get_standev_objtype(canindex index, cansubind subind)
{
	struct object obj;

	obj.index = index;
	obj.subind = subind;
	get_object_standev(&obj);
	if (obj.size <= 0) return (int16)obj.size;
	return obj.deftype;
}

// Функция побайтового чтения CANopen объекта из объектного словаря
// Обслуживает объекты в диапазоне индексов 0x6000..0x9FFF
int16 server_read_standev_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size, cnt;
	canbyte *bpnt;
	struct object obj;

	obj.index = index;
	obj.subind = subind;
	get_object_standev(&obj);
	if (obj.size <= 0) return (int16)obj.size;
	if ((obj.access & CAN_MASK_ACCESS_RO) == 0) return CAN_ERRET_OBD_WRITEONLY;
	size = obj.size;
	bpnt = obj.pnt;
	OBJECT_DICTIONARY_TO_CANOPEN
	return CAN_RETOK;
}

// Функция побайтовой записи CANopen объекта в объектный словарь
// Обслуживает объекты в диапазоне индексов 0x6000..0x9FFF
int16 server_write_standev_objdict(canindex index, cansubind subind, canbyte *data)
{
	int16 size, cnt;
	canbyte *bpnt;
	struct object obj;

	obj.index = index;
	obj.subind = subind;
	get_object_standev(&obj);
	if (obj.size <= 0) return (int16)obj.size;
	if ((obj.access & CAN_MASK_ACCESS_WO) == 0) return CAN_ERRET_OBD_READONLY;
	size = obj.size;
	bpnt = obj.pnt;
	FROM_CANOPEN_TO_OBJECT_DICTIONARY
	return CAN_RETOK;
}

void enter_error_state(void)
{
}

void exit_error_state(void)
{
}

void start_hardware(void)
{
}

void stop_hardware(void)
{
}

void application_timer_routine(void)
{
	// Вызывается из CANopen таймера
	// Здесь можно задать значения объекта для отладки.
  
//	transmit_can_pdo(0x1800);	// Пример передачи TPDO с типом передачи 254 или 255
								// В качестве аргумента используется индекс коммуникационного объекта TPDO
}

void application_monitor_routine(void)
{
	// Вызывается из CANopen монитора (главного цикла программы)
	// Здесь можно задать значения объекта для отладки.
}

void slave_init_standev_application(void)
{
	unsigned8 chan;

	for (chan = 0; chan < 4; chan++) {
		sample_data[chan] = 0;
	}
	// Здесь можно (пере)инициализировать прикладные данные, используемые в качестве CANopen объектов.
}

void slave_init_standev_communication(void)
{
  
	// Настройка PDO отображения двух TPDO для CANopen объектов
  
	server_write_obd_u32(0x1A00, 0, 0);				// Деакцивация первого TPDO (PDO invalid)
	server_write_obd_u32(0x1A00, 1, 0x61000120);	// Отображение первого субиндекса (нулевой элемент массива) в первое TPDO
	server_write_obd_u32(0x1A00, 2, 0x61000220);	// Отображение второго субиндекса (первый элемент массива) в первое TPDO
	server_write_obd_u32(0x1A00, 0, 2);				// Запись числа объектов, отображаемых в первое TPDO (два)


	server_write_obd_u32(0x1A01, 0, 0);				// Деакцивация второго TPDO (PDO invalid)
	server_write_obd_u32(0x1A01, 1, 0x61000320);	// Отображение третьего субиндекса (второй элемент массива) во второе TPDO
	server_write_obd_u32(0x1A01, 2, 0x61000420);	// Отображение четвертого субиндекса (третий элемент массива) во второе TPDO
	server_write_obd_u32(0x1A01, 0, 2);				// Запись числа объектов, отображаемых во второе TPDO (два)
	
	server_write_obd_u32(0x1800, 0x1, 0x80000184);	// Пере-настройка COB-ID первого TPDO на значение 0x184 в не активированном состоянии (PDO invalid)
													// Только при необходимости пере-настройки предопределенного распределения CANopen идентификаторов
													// Здесь также может быть использовано активированное значение PDO COB-ID 0x00000184 (PDO valid)

	server_write_obd_u32(0x1801, 0x1, 0x80000194);	// Пере-настройка COB-ID второго TPDO на значение 0x194 в не активированном состоянии (PDO invalid)
													// Только при необходимости пере-настройки предопределенного распределения CANopen идентификаторов
													// Здесь также может быть использовано активированное значение PDO COB-ID 0x00000194 (PDO valid)

	set_pdo_state(0x1800, VALID);					// Активация первого TPDO (PDO valid)
	set_pdo_state(0x1801, VALID);					// Активация второго TPDO (PDO valid)

}

void application_init_device_routine(void)
{
}

#endif
