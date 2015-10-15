
#include "ubberFrame.h"
#include <string.h>

#define FRAME_FLAGS_OFFSET 0
#define FRAME_SOURCEID_OFFSET 1
#define FRAME_DESTID_OFFSET 2
#define FRAME_TYPE_OFFSET 3
#define FRAME_PAYLOADSIZE_OFFSET 4
#define FRAME_PAYLOAD_OFFSET 5

//<<constructor>> Create a empty UbberFrame
UbberFrame::UbberFrame()
{
	this->data.payloadSize = 0;
}

//<<desctructor>>
UbberFrame::~UbberFrame()
{
}


//<<constructor>> Create a frame fr
UbberFrame::UbberFrame(const uint8_t data[], const unsigned int length)
{
	frameFromChar(data, length);
}

int UbberFrame::frameFromChar(const uint8_t data[], const unsigned int length)
{
	if(length < HEADER_SIZE || length != HEADER_SIZE + data[FRAME_PAYLOADSIZE_OFFSET])
		return -1;

	
	this->data.flags = data[FRAME_FLAGS_OFFSET];
	this->data.sourceID = data[FRAME_SOURCEID_OFFSET];
	this->data.destID = data[FRAME_DESTID_OFFSET];
	this->data.type = data[FRAME_TYPE_OFFSET];
	this->data.payloadSize = data[FRAME_PAYLOADSIZE_OFFSET] < MAX_PAYLOAD_SIZE ? data[FRAME_PAYLOADSIZE_OFFSET] : 256;
	if(this->data.payloadSize)
		memcpy(this->data.payload, &data[FRAME_PAYLOAD_OFFSET], this->data.payloadSize);
	else
		this->data.payload[0] = '\0';

	return 0;
	
}

const uint8_t * UbberFrame::frameToChar()
{
	return this->data.data;
}


uint8_t UbberFrame::operator[](int index)
{
	return this->data.data[index];
}


#define GEN_DATA_GETTER(__type, __name, __attribute) \
	__type UbberFrame::__name () { \
		return this->data.__attribute ; \
	}


#define GEN_DATA_SETTER(__type, __name, __attribute) \
	int UbberFrame::__name (__type __attribute) { \
		this->data.__attribute = __attribute; \
	}


GEN_DATA_GETTER(uint8_t, getFlags, flags)
GEN_DATA_GETTER(uint8_t, getSourceID, sourceID)
GEN_DATA_GETTER(uint8_t, getDestID, destID)
GEN_DATA_GETTER(uint8_t, getType, type)
GEN_DATA_GETTER(uint8_t, getPayloadSize, payloadSize)
GEN_DATA_GETTER(const uint8_t *, getPayload, payload)


GEN_DATA_SETTER(uint8_t, setFlags, flags)
GEN_DATA_SETTER(uint8_t, setSourceID, sourceID)
GEN_DATA_SETTER(uint8_t, setDestID, destID)
GEN_DATA_SETTER(uint8_t, setType, type)


int UbberFrame::setPayload(const uint8_t payload[], unsigned int size)
{
	if(size > MAX_PAYLOAD_SIZE)
		return -1;

	this->data.payloadSize = size;
	memcpy(this->data.payload, payload, this->data.payloadSize);

	return 0;
}


unsigned int UbberFrame::getLength()
{
	return HEADER_SIZE + this->data.payloadSize;
}



char * UbberFrame::typeString(enum type type)
{

	 switch(type) {
	 case PAYLOAD_DEFINED:
		  return "PAYLOAD_DEFINED";
	 case PAUSE:
		  return "PAUSE";
	 case RENCONTRE:
		  return "RENCONTRE";
	 case REPAS:
		  return "REPAS";
	 case CLOPE:
		  return "CLOPE";
	 case CAFE:
		  return "CAFE";
	 case PISCINE:
		  return "PISCINE";
	 case EPICURIA:
		  return "EPICURIA";
	 case VELO:
		  return "VELO";
	 case MAJ:
		  return "MISE A JOUR";
	 default:
		  return NULL;
	}
}

char * UbberFrame::getTypeString()
{
	 return typeString((enum type)this->data.type);
}

char * UbberFrame::iDString(enum id id)
{
	 switch(id) {
	 case BEN_M:
		  return "Benjamin Mingez";
	 case CLEMENT:
		  return "Clément Léger";
	 case JEJE:
		  return "Jérome Reybert";
	 case MARC:
		  return "Marc Poulhiès";
	 case GUILLAUME_S:
		  return "Guillaume Sarrazin";
	 case DAMS:
		  return "Damien Cottier";
	 case GUILLAUME_L:
		  return "Guillaume Lager";
	 case ALL:
		  return "Broadcast";
	 default:
		  return NULL;
	 }
}

char * UbberFrame::getSourceIDString()
{
	 return iDString((enum id)this->data.sourceID);
}

char * UbberFrame::getDestIDString()
{
	 return iDString((enum id)this->data.destID);
}
