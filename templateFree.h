#pragma once
#include"symbolDef.h"

template<typename CLASS_NAME, typename CLASS_MEMBER_TYPE, typename CLASS_MEMBER_MEMBER_TYPE>class CLASS_TFREE
{
public:
	CLASS_TFREE() :m_p(&crypto_t::cipher), m_member_p(&cipher_t::info), m_member_pMethod(&cipher_t::method)
	{
	};
	void operator()(CLASS_NAME* obj)
	{
		if (obj != NULL)
		{
			if (obj->*m_p != NULL)
			{
				if ((obj->*m_p)->*m_member_p != NULL)
				{
					/*
					if (method == SALSA20 || method == CHACHA20 || method == CHACHA20IETF)
					*/
					if ((obj->*m_p)->*m_member_pMethod == SALSA20 || (obj->*m_p)->*m_member_pMethod == CHACHA20 || (obj->*m_p)->*m_member_pMethod == CHACHA20IETF)
						free((obj->*m_p)->*m_member_p);
				}
				free(obj->*m_p);
			}
			free(obj);
		}
	}
private:
	CLASS_MEMBER_TYPE* CLASS_NAME::* m_p;
	CLASS_MEMBER_MEMBER_TYPE* CLASS_MEMBER_TYPE::* m_member_p;
	int CLASS_MEMBER_TYPE::* m_member_pMethod;
};

template<typename CLASS_NAME> using CRYPTO_TFREE = class CLASS_TFREE<CLASS_NAME, cipher_t, cipher_kt_t>;

template<typename Arg1, typename resultType = void> class ctxfree
{
public:
	ctxfree() :m_lpfun(&stream_ctx_release)
	{
	}
	void operator()(Arg1* parg)
	{
		(*m_lpfun)(parg);
		free(parg);
	}
protected:
	resultType(*m_lpfun)(Arg1*);
};

template<typename Arg1> using ctxfreefunReturnVoid = class ctxfree<Arg1, void>;

