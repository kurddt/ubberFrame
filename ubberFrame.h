#ifndef __UBBER_H_
#undef __UBBER_H_

//#include <Arduino.h>
#include <stdint.h>

class UbberFrame {
public:
	//Constructores
	UbberFrame();
	UbberFrame(const uint8_t data[], const unsigned int length);
	//desctructor
	~UbberFrame();
	int frameFromChar(const uint8_t data[], const unsigned int length);
	const uint8_t * frameToChar();
	//operators
	uint8_t operator[](int);

	//getter
	uint8_t getFlags();
	uint8_t getSourceID();
	uint8_t getDestID();
	uint8_t getType();
	uint8_t getPayloadSize();
	const uint8_t * getPayload();

	//setter
	int setFlags(uint8_t);
	int setSourceID(uint8_t);
	int setDestID(uint8_t);
	int setType(uint8_t);
	int setPayload(const uint8_t payload[], unsigned int size);
private:
	enum type {
		PAYLOAD_DEFINED = 0,
		PAUSE			= 1,
	};
	struct frame {
		union {
			struct {
				uint8_t flags;
				uint8_t sourceID;
				uint8_t destID;
				uint8_t type;
				uint8_t payloadSize;
				uint8_t payload[256];
			};
			uint8_t data[];
		};
	};

	struct frame data;
};


#endif //__UBBER_H_ */
