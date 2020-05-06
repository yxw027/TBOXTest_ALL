#ifndef SINGLETONBASE_H
#define SINGLETONBASE_H

#ifndef NULL
#define NULL (0)
#endif

template <typename T>

class CSingletonBase
{
public:
    __inline static T* GetInstance()
    {
        return m_instance;
    }
    __inline static void FreeInstance()
    {
        if (m_instance != NULL)
        {
            delete m_instance;
        }
        m_instance = NULL;
    }
private:
    CSingletonBase(){;}
    CSingletonBase(const CSingletonBase&){;}
    CSingletonBase &operator=(const CSingletonBase&){;}
    virtual ~CSingletonBase(){;}

private:
    static	T* m_instance;
};

template <typename T>

T* CSingletonBase<T>::m_instance = new T();

#define REGISTER_SINGLETON(Class) \
    public: \
    friend class CSingletonBase<Class>; \
	private: \
	Class(){} \
	virtual ~Class(){}

#define GET_SINGLETON_INSTANCE(Class) \
    CSingletonBase<Class>::GetInstance()

#define RELEASE_SINGLETON_INSTANCE(Class) \
    CSingletonBase<Class>::FreeInstance()

#endif // SINGLETONBASE_H
