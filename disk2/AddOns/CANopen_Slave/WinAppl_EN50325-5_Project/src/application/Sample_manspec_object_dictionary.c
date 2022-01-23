#include <DS401_header.h>

#if CHECK_VERSION_APPL(2, 1, 1)
//  CHECK_VERSION_APPL(2, 0, 0)
//  CHECK_VERSION_APPL(1, 2, 0)


#if (IOREMOTE_APPLICATION_MODE == APPLICATION_TEST)
#if (IOREMOTE_PRINTF_MODE == ON)
void print_appl(void *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vfprintf(stdout, (char *)fmt, ap);
	va_end(ap);
}
#else
void print_appl(void *fmt, ...)
{
}
#endif
#endif


union
{
  char buf [8];
  struct {
    char count;
    short int  d1;
    short int  d2;
    short int  d3;
    char reserv;
  } data;
} mess_214;

// Функция определения CANopen объектов.
// Формирует прикладной объектный словарь CANopen на основе существующих прикладных данных.
static void get_object_standev(struct object *obj)
{
	obj->size = CAN_ERRET_OBD_NOSUBIND;
	obj->deftype = 0;
	obj->access = 0;
	obj->pnt = NULL;

	// Описание CANopen объектов - пример объекта без субиндексов.
	// В этом случае само значение объекта доступно по нулевому субиндексу.
	
	if (obj->index == 0x2100) {		// Значение индекса объекта, выбранное пользователем.
		if (obj->subind == 0) {
			obj->size = sizeof(unsigned8);
			obj->deftype = CAN_DEFTYPE_UNSIGNED8;
			obj->access = CAN_MASK_ACCESS_RO | CAN_MASK_ACCESS_PDO;		// Доступ только по чтению и возможность PDO отображения
			obj->pnt = (canbyte*)&mess_214.data.count;	// Объект приложения
		}
		return;
	}

	if (obj->index == 0x2101) {		// Значение индекса объекта, выбранное пользователем.
		if (obj->subind == 0) {
			obj->size = sizeof(int16);
			obj->deftype = CAN_DEFTYPE_INTEGER16;
			obj->access = CAN_MASK_ACCESS_RW | CAN_MASK_ACCESS_PDO;		// Доступ по чтению, записи и возможность PDO отображения
			obj->pnt = (canbyte*)&mess_214.data.d1;	// Объект приложения
		}
		return;
	}

	if (obj->index == 0x2102) {		// Значение индекса объекта, выбранное пользователем.
		if (obj->subind == 0) {
			obj->size = sizeof(int16);
			obj->deftype = CAN_DEFTYPE_INTEGER16;
			obj->access = CAN_MASK_ACCESS_RW | CAN_MASK_ACCESS_PDO;		// Доступ по чтению, записи и возможность PDO отображения
			obj->pnt = (canbyte*)&mess_214.data.d2;	// Объект приложения
		}
		return;
	}

	if (obj->index == 0x2103) {		// Значение индекса объекта, выбранное пользователем.
		if (obj->subind == 0) {
			obj->size = sizeof(int16);
			obj->deftype = CAN_DEFTYPE_INTEGER16;
			obj->access = CAN_MASK_ACCESS_RW | CAN_MASK_ACCESS_PDO;		// Доступ по чтению, записи и возможность PDO отображения
			obj->pnt = (canbyte*)&mess_214.data.d3;	// Объект приложения
		}
		return;
	}

	if (obj->index == 0x2104) {		// Значение индекса объекта, выбранное пользователем.
		if (obj->subind == 0) {
			obj->size = sizeof(unsigned8);
			obj->deftype = CAN_DEFTYPE_UNSIGNED8;
			obj->access = CAN_MASK_ACCESS_RO | CAN_MASK_ACCESS_PDO;		// Доступ только по чтению и возможность PDO отображения
			obj->pnt = (canbyte*)&mess_214.data.reserv;	// Объект приложения
		}
		return;
	}
	obj->size = CAN_ERRET_OBD_NOOBJECT;
}

// Функция запроса размера CANopen объекта
// Обслуживает объекты в диапазоне индексов 0x2000..0x5FFF
int32 server_get_manspec_objsize(canindex index, cansubind subind)
{
	struct object obj;

	obj.index = index;
	obj.subind = subind;
	get_object_standev(&obj);
	return obj.size;
}

// Функция запроса вида доступа к CANopen объекту
// Обслуживает объекты в диапазоне индексов 0x2000..0x5FFF
int16 server_see_manspec_access(canindex index, cansubind subind)
{
	struct object obj;

	obj.index = index;
	obj.subind = subind;
	get_object_standev(&obj);
	if (obj.size <= 0) return (int16)obj.size;
	return obj.access;
}

// Функция запроса типа CANopen объекта
// Обслуживает объекты в диапазоне индексов 0x2000..0x5FFF
int16 server_get_manspec_objtype(canindex index, cansubind subind)
{
	struct object obj;

	obj.index = index;
	obj.subind = subind;
	get_object_standev(&obj);
	if (obj.size <= 0) return (int16)obj.size;
	return obj.deftype;
}

// Функция побайтового чтения CANopen объекта из объектного словаря
// Обслуживает объекты в диапазоне индексов 0x2000..0x5FFF
int16 server_read_manspec_objdict(canindex index, cansubind subind, canbyte *data)
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
// Обслуживает объекты в диапазоне индексов 0x2000..0x5FFF
int16 server_write_manspec_objdict(canindex index, cansubind subind, canbyte *data)
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

void slave_init_manspec_application(void)
{
	// Здесь можно (пере)инициализировать прикладные данные, используемые в качестве CANopen объектов.
}

void slave_init_manspec_communication(void)
{
  
	// Настройка PDO отображения для CANopen объектов
  
	server_write_obd_u32(0x1A02, 0, 0);				// Деакцивация третьего TPDO (PDO invalid)
	server_write_obd_u32(0x1A02, 1, 0x21000008);	// Отображение объекта 0x2100 длиной 8 бит в третье TPDO
	server_write_obd_u32(0x1A02, 2, 0x21010010);	// Отображение объекта 0x2101 длиной 16 бит в третье TPDO
	server_write_obd_u32(0x1A02, 3, 0x21020010);	// Отображение объекта 0x2102 длиной 16 бит в третье TPDO
	server_write_obd_u32(0x1A02, 4, 0x21030010);	// Отображение объекта 0x2103 длиной 16 бит в третье TPDO
	server_write_obd_u32(0x1A02, 5, 0x21040008);	// Отображение объекта 0x2104 длиной 8 бит в третье TPDO
	server_write_obd_u32(0x1A02, 0, 5);				// Запись числа объектов, отображаемых в третье TPDO (пять)
													// Полная длина данных PDO составит 64 бит (8 байт)
	
	server_write_obd_u32(0x1802, 0x2, 2);			// Привязка передачи PDO к каждому второму SYNC - при необходимости

	server_write_obd_u32(0x1802, 0x1, 0x80000214);	// Пере-настройка COB-ID третьего TPDO на значение 0x214 в не активированном состоянии (PDO invalid)
													// Осуществляется только при необходимости пере-настройки предопределенного распределения CANopen идентификаторов
													// Здесь также может быть использовано активированное значение PDO COB-ID 0x00000214 (PDO valid)

	set_pdo_state(0x1802, VALID);					// Активация третьего TPDO (PDO valid)
}

#endif
