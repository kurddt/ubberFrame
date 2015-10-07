
#include "ubberFrame.h"
#include <string.h>
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
	if(length < 6 && length < 6 + data[4])
		return -1;

	
	this->data.flags = data[0];
	this->data.sourceID = data[1];
	this->data.destID = data[2];
	this->data.type = data[3];
	this->data.payloadSize = data[4] < 256 ? data[4] : 256;
	memcpy(this->data.payload, &data[5], this->data.payloadSize);	
	
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
	if(size > 255)
		return -1;

	this->data.payloadSize = size;
	memcpy(this->data.payload, payload, this->data.payloadSize);

	return 0;
}


unsigned int UbberFrame::getLength()
{
	return 5 + this->data.payloadSize;
}
