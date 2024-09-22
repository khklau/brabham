#pragma once

#include "action.hpp"

#include <raceman.h>


namespace torcs {
namespace brabham {

// forward declarations
struct race_context;

class driver
{
public:
    driver(const race_context& context);
    action drive(const tCarElt& car, const tSituation& situation) const;
private:
    const race_context& context_;
};

} // namespace brabham
} // namespace torcs
