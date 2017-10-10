#ifndef ARDUINOPIN_H
#define ARDUINOPIN_H

#include <Arduino.h>
#include <inttypes.h>

class ArduinoPin
{
private:
#if defined (__arm__) && defined (__SAM3X8E__)
	uint32_t  m_bit;
	Pio * m_port;
    
	void setBit(uint32_t n) { m_bit = n; }
	void setPort(Pio *   n) { m_port = n; }
#else
	uint8_t  m_bit;
	uint8_t m_port;
    
	void setBit(uint8_t  n) { m_bit = n; }
	void setPort(uint8_t n) { m_port = n; }

#endif

	uint8_t m_pin;
	uint8_t m_mode;

protected:
#if defined (__arm__) && defined (__SAM3X8E__)
	uint32_t getBit() const { return m_bit; }
	Pio *    port() const { return m_port; }
#else
	uint8_t getBit() const { return m_bit; }
	uint8_t port() const { return m_port; }
#endif
public:
	ArduinoPin(uint8_t pin, uint8_t mode);
	~ArduinoPin() {}

	uint8_t pin() const { return m_pin; }

	uint8_t mode() const { return m_mode; }
};

#if defined (__arm__) && defined (__SAM3X8E__)
	#define GPIO_REGISTER_TYPE uint32_t
#elif defined ARDUINO_ARCH_AVR
	#define GPIO_REGISTER_TYPE uint8_t
#elif defined ARDUINO_ARCH_ESP8266
	#define GPIO_REGISTER_TYPE uint32_t
#elif defined ARDUINO_ARCH_ESP32
	#define GPIO_REGISTER_TYPE uint32_t
#else
	#define GPIO_REGISTER_TYPE uint8_t
#endif

class ArduinoInputPin : public ArduinoPin
{
private:
	volatile GPIO_REGISTER_TYPE *m_in;

	volatile GPIO_REGISTER_TYPE *in() const { return m_in; }

public:
	ArduinoInputPin(uint8_t pin);
	~ArduinoInputPin() {}

	uint8_t read() const { return *in() & getBit(); }
};


class ArduinoOutputPin : public ArduinoPin
{
private:
	volatile GPIO_REGISTER_TYPE *m_out;

	volatile GPIO_REGISTER_TYPE *out() const { return m_out; }

public:
	ArduinoOutputPin(uint8_t pin);
	~ArduinoOutputPin() {}

#if defined (__arm__) && defined (__SAM3X8E__)
	void clr() const { *out() &= ~getBit(); }
	void set() const { *out() |= getBit(); }
#else
	void clr() const { *out() &= ~getBit(); }
	void set() const { *out() |= getBit(); }
#endif
};

#endif // ARDUINOPIN_H
