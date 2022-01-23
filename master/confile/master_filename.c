#include <master_header.h>

#if CHECK_VERSION_APPL(1, 1, 1)

#ifdef CAN_OS_WIN32
void transform_file_name(char *fname, char *initfn)
{
	unsigned16 slhp, cnt, c1;
	wchar_t *cmd_line;

	slhp = 0;
	if (initfn[0] == '\\') {
		cnt = 1;
	} else {
		cmd_line = SysAllocString(GetCommandLine());
		c1 = 0;
		for (cnt = 0; cnt < STR_FILE_NAME_SIZE-1; cnt++) {
			if (cmd_line[cnt] == '\0') break;
			if (cmd_line[cnt] != '"') {
				fname[c1] = (char)cmd_line[cnt];
				if (fname[c1] == '\\') slhp = c1+1;
				c1++;
			}
		}
		cnt = 0; 
	}
	while (slhp < STR_FILE_NAME_SIZE-1) {
		if (initfn[cnt] == '\0') break;
		fname[slhp] = initfn[cnt];
		slhp++; cnt++;
	}
	while (slhp < STR_FILE_NAME_SIZE-1) {
		fname[slhp] = '\0';
		slhp++;
	}
	fname[STR_FILE_NAME_SIZE-1] = '\0';
}
#endif

void time_stamp_file_name(char *fname, char *initfn)	// 1.1.1 renamed
{
	unsigned16 cnt, pntp, fnap;
	time_t ts;
	struct tm tp;
	char tstxt[STR_TS_SIZE];

	ts = time(NULL);
	tp = *localtime(&ts);
	strftime(tstxt, STR_TS_SIZE, "_%Y%m%d_%H%M", &tp);		// 14 symbols
	pntp = 0;
	fnap = 0;
	for (cnt = 0; cnt < STR_FILE_NAME_SIZE-1; cnt++) {
		if (initfn[cnt] == '\0') break;
		fname[fnap] = initfn[cnt];
		if (initfn[cnt] == '.') pntp = cnt+1;
		fnap++;
	}
	if (pntp > 0) fnap = pntp - 1;
	if (fnap >= STR_FILE_NAME_SIZE-1-14) fnap = STR_FILE_NAME_SIZE-1-14;
	for (cnt = 0; cnt < 14; cnt++) {
		fname[fnap] = tstxt[cnt];
		fnap++;
	}
	if (pntp > 0) {
		pntp -= 1;
		while (fnap < STR_FILE_NAME_SIZE-1) {
			if (initfn[pntp] == '\0') break;
			fname[fnap] = initfn[pntp];
			fnap++; pntp++;
		}
	}
	while (fnap < STR_FILE_NAME_SIZE-1) {
		fname[fnap] = '\0';
		fnap++;
	}
	fname[STR_FILE_NAME_SIZE-1] = '\0';
}

#endif
