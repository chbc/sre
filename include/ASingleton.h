#ifndef _A_SINGLETON_H_
#define _A_SINGLETON_H_

namespace sre
{

class ASingleton
{
protected:
    virtual void init() {};
    virtual void release() {};

friend class SingletonsManager;
};

}

#endif