#include "streamCrypto.h"
#include<exception>
#include<thread>

streamCrypto::streamCrypto(const char* password, const char* method)
{
	try
	{
		auto ptr = crypto_init(password, NULL, method);
		m_streamCrypto.reset(ptr);
		m_streamDeCtx.reset((cipher_ctx_t*)malloc(sizeof(cipher_ctx_t)));
		m_streamEnCtx.reset((cipher_ctx_t*)malloc(sizeof(cipher_ctx_t)));

		if (m_streamEnCtx.get() == NULL || m_streamDeCtx.get() == NULL)
			throw std::exception("out of memory");
		m_streamCrypto->ctx_init(m_streamCrypto->cipher, m_streamEnCtx.get(), 1);
		m_streamCrypto->ctx_init(m_streamCrypto->cipher, m_streamDeCtx.get(), 0);
	}
	catch (std::exception & e) 
	{
	
	}
}

int streamCrypto::encrypt(buffer_t* buff)
{
	return m_streamCrypto->encrypt(buff, &*m_streamEnCtx, buff->capacity);
}

int streamCrypto::encrypt_all(buffer_t* buff)
{
	m_streamCrypto->encrypt_all(buff, m_streamCrypto->cipher, buff->capacity);
	return 0;
}

int streamCrypto::decrypt(buffer_t* buff)
{
	m_streamCrypto->decrypt(buff, &*m_streamDeCtx, buff->capacity);
	return 0;
}

int streamCrypto::decrypt_all(buffer_t* buff)
{
	m_streamCrypto->decrypt_all(buff, m_streamCrypto->cipher, buff->capacity);
	return 0;
}
