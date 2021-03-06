#ifndef __UBBER_H_
#undef __UBBER_H_

//#include <Arduino.h>
#include <stdint.h>

#define MAX_PAYLOAD_SIZE 255

class UbberFrame {
public:
	//Constructores
	UbberFrame();
	UbberFrame(const uint8_t data[], const unsigned int length);
	//desctructor
	~UbberFrame();

	/**
	 * Copy a uint8_t array to an UbberFrame
	 */
	int frameFromChar(const uint8_t data[], const unsigned int length);

	/**
	 * Return the frame content as a char. This is not a copy !
	 */
	const uint8_t * frameToChar();

	/**
	 * Get the UbberFrame length
	 */
	unsigned int getLength();

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
	void setFlags(uint8_t);
	void setSourceID(uint8_t);
	void setDestID(uint8_t);
	void setType(uint8_t);
	int setPayload(const uint8_t payload[], unsigned int size);
	
	enum type {
		PAYLOAD_DEFINED = 0x0,
		PAUSE			= 0x1,
		RENCONTRE		= 0x2,
		REPAS			= 0x3,
		CLOPE			= 0x4,
		CAFE			= 0x5,
		PISCINE			= 0x6,
		EPICURIA		= 0x7,
		VELO			= 0x8,
		ACQUITTEMENT	= 0xa,
		MAJ				= 0xff,
	};

	enum id {
		BEN_M		= 0x1,
		CLEMENT		= 0x2,
		JEJE		= 0x3,
		MARC		= 0x4,
		GUILLAUME_S	= 0x5,
		DAMS		= 0x6,
		GUILLAUME_L	= 0x7,
		ALL			= 0xff,
	};

	/* printable */
	static const char * iDString(enum id id);
	static const char * typeString(enum type type);
	const char * getTypeString();
	const char * getSourceIDString();
	const char * getDestIDString();
private:
	struct frame {
		union {
			struct {
				uint8_t flags;
				uint8_t sourceID;
				uint8_t destID;
				uint8_t type;
				uint8_t payloadSize;
				uint8_t payload[MAX_PAYLOAD_SIZE];
			};
			uint8_t data[];
		};
	};
	struct frame data;

	const unsigned int HEADER_SIZE = sizeof(struct frame) - MAX_PAYLOAD_SIZE;
	
};

#endif //__UBBER_H_ */
