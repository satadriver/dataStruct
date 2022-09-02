

unsigned short crc16(unsigned char * data, int size) {

	int cnt = size >> 1;
	int mod = size % 2;

	unsigned int v = 0;

	unsigned short *crcdata = (unsigned short*)data;

	for (int i = 0;i < cnt; i ++)
	{
		v += crcdata[i];
	}
	
	if (mod)
	{
		v += data[cnt * 2];
	}

	unsigned int high16 = v >> 16;
	v = v & 0xffff;
	v += high16;
	return v;
}