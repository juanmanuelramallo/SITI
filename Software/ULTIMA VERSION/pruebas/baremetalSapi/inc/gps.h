void gpsFrameCharacterReceivedInit(void);

void gpsFrameFlagsInit(void);

void gpsFrameFieldInit(char* frameField);

void gpsFrameVarInit(void);

void gpsSetCharacterReceived(uint8_t frameCharacter);

uint8_t gpsReadCharacterReceived(void);

uint8_t gpsReadFlagCharacterReceived(void);

void gpsSetFlagCharacterReceived(void);

void gpsClearFlagCharacterReceived(void);

uint8_t gpsReadFlagReady(void);

void gpsSetFlagReady(void);

void gpsClearFlagReady(void);

uint8_t* gpsReadLatitude(void);

uint8_t* gpsReadLongitude(void);

void gpsFrameParse(uint8_t frameCharacter);

uint8_t* gpsReadLatitudeUbidots(void);

uint8_t* gpsReadLongitudeUbidots(void);

uint8_t gpsValidateCharacter(uint8_t character);

void gpsVarPrint(void);