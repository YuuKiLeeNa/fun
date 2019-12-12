#pragma once
#include<memory>
#include "templateFree.h"

class streamCrypto 
{
public:
	streamCrypto(const char*password, const char*method = "aes-256-cfb");

	/*
	CRYPTO_OK = 0, CRYPTO_ERROR=-2, CRYPTO_NEED_MORE = -1;
	*/

	//CRYPTO_OK,CRYPTO_ERROR
	int encrypt(buffer_t*buff);
	//CRYPTO_OK,CRYPTO_ERROR
	int encrypt_all(buffer_t* buff);
	//CRYPTO_OK, CRYPTO_ERROR, CRYPTO_NEED_MORE
	int decrypt(buffer_t* buff);
	//CRYPTO_OK, CRYPTO_ERROR
	int decrypt_all(buffer_t* buff);

protected:

	std::unique_ptr<crypto_t, CRYPTO_TFREE<crypto_t>> m_streamCrypto;
	std::unique_ptr<cipher_ctx_t, ctxfreefunReturnVoid<cipher_ctx_t>> m_streamDeCtx;
	std::unique_ptr<cipher_ctx_t, ctxfreefunReturnVoid<cipher_ctx_t>> m_streamEnCtx;
};