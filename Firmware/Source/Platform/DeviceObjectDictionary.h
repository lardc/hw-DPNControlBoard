#ifndef __DEV_OBJ_DIC_H
#define __DEV_OBJ_DIC_H

// Команды
#define ACT_ENABLE_POWER				1	// Переход в состояние ожидания
#define ACT_DISABLE_POWER				2	// Отключение блока
#define ACT_FAULT_CLEAR					3	// Очистка fault
#define ACT_WARNING_CLEAR				4	// Очистка warning
//
#define ACT_DBG_CLAMP_ADAPTER			10	// Управление адаптеров в отладочном режиме
#define ACT_DBG_SET_TOP_POSITION		11	// Установить тест верхнего ключа в отладочном режиме
#define ACT_DBG_SET_BOT_POSITION		12	// Установить тест нижнего ключа в отладочном режиме
#define ACT_DBG_SET_COIL				13	// Установить индуктивность в отладочном режиме
#define ACT_DBG_CHARGE					14	// Управление зарядом в отладочном режиме
#define ACT_DBG_DISCHARGE				15	// Управление разрядом в отладочном режиме
#define ACT_DBG_HV_MEASURE				16	// Получение сырых данных HV напряжения в отладочном режиме
#define ACT_DBG_PRESSURE_MEASURE		17	// Получение сырых данных давления в отладочном режиме
//
#define ACT_SAVE_TO_ROM					200	// Сохранение пользовательских данных во FLASH процессора
#define ACT_RESTORE_FROM_ROM			201	// Восстановление данных из FLASH
#define ACT_RESET_TO_DEFAULT			202	// Сброс DataTable в состояние по умолчанию
//
#define ACT_BOOT_LOADER_REQUEST			320	// Перезапуск процессора с целью перепрограммирования
// -----------------------------

// Регистры
// Сохраняемые регистры

//

// Несохраняемы регистры чтения-записи

//
#define REG_DBG							150	// Отладочный регистр

// Регистры только чтение
#define REG_DEV_STATE					192	// Регистр состояния
#define REG_FAULT_REASON				193	// Регистр Fault
#define REG_DISABLE_REASON				194	// Регистр Disable
#define REG_WARNING						195	// Регистр Warning
#define REG_PROBLEM						196	// Регистр Problem
#define REG_OP_RESULT					197	// Регистр результата операции
#define REG_SELF_TEST_OP_RESULT			198	// Регистр результата самотестирования
#define REG_SUB_STATE					199	// Регистр вспомогательного состояния
//
#define REG_FWINFO_SLAVE_NID			256	// Device CAN slave node ID
#define REG_FWINFO_MASTER_NID			257	// Device CAN master node ID (if presented)
// 258 - 259
#define REG_FWINFO_STR_LEN				260	// Length of the information string record
#define REG_FWINFO_STR_BEGIN			261	// Begining of the information string record
// -----------------------------

// Endpoints

// Operation results
#define OPRESULT_NONE					0	// No information or not finished
#define OPRESULT_OK						1	// Operation was successful
#define OPRESULT_FAIL					2	// Operation failed

// Fault and disable codes
#define DF_NONE							0	// Ошибок нет

// Warning
#define WARNING_NONE					0	// Предупреждений нет

// Problem
#define PROBLEM_NONE					0

// User Errors
#define ERR_NONE						0
#define ERR_CONFIGURATION_LOCKED		1	// Устройство защищено от записи
#define ERR_OPERATION_BLOCKED			2	// Операция не может быть выполнена в текущем состоянии устройства
#define ERR_DEVICE_NOT_READY			3	// Устройство не готово для смены состояния
#define ERR_WRONG_PWD					4	// Неверный ключ безопасности

#endif // __DEV_OBJ_DIC_H
