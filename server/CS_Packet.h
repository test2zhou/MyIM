#ifndef __CS_PACKET_H__
#define __CS_PACKET_H__

#include <string>

#define DEFAULT_LEN 256

class CPacket
{
public:
	CPacket(UINT16 protocol, UINT32 len = DEFAULT_LEN);
	CPacket(char* , UINT32);	
	virtual ~CPacket(void);

	static CPacket* Create(char* , UINT32);
	
	void setProtocol(UINT16);
	char* getBuffer() const;
	UINT32 getLength() const;

	void writeData(void* , size_t );
	void readData(void* , size_t );

	void writeString(std::string&);
	void readString(std::string&);

	bool expand(size_t sz);

	template<typename T>
	void writeInt(T a) {
		size_t s = sizeof(T);
		writeData(&a, s);
	}

	template<typename T>
	void readInt(T &a) {
		size_t s = sizeof(T);
		readData(&a, s);
	}

	template<typename T>
	void writeUInt(T a) {
		size_t s = sizeof(T);
		if (s == sizeof(UINT32)) {
			UINT32 b = htonl(a);
			writeData(&b, s);
		} else if (s == sizeof(UINT16)) {
			UINT16 b = htons(a);
			writeData(&b, s);
		} else {
			writeData(&a, s);
		}
	}

	template<typename T>
	void readUInt(T &a) {
		size_t s = sizeof(T);
		if (s == sizeof(UINT32)) {
			readData(&a, s);
			a = ntohl(a);
		} else if (s == sizeof(UINT16)) {
			readData(&a, s);
			a = ntohs(a);
		} else {
			readData(&a, s);
		}
	}
	
	void* operator new (size_t sz) {return ::malloc(sz);}
	void  operator delete (void* ptr) {return ::free(ptr);}

private:
	UINT16 m_sProtocol;
	UINT8 m_cVersion;

	char* m_pBuff;
	char* m_pCurr;
	UINT32 m_nLen;


};

#endif// __CS_PACKET_H__
