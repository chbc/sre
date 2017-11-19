#include "SingletonsManager.h"

namespace sre
{

UPTR<SingletonsManager> SingletonsManager::instance;

void SingletonsManager::release()
{
    for (std::pair<const std::string, UPTR<ISingleton>> &item : this->singletons)
        item.second->release();

    this->singletons.clear();
}

} // namespace
