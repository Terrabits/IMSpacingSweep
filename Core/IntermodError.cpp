#include "IntermodError.h"


IntermodError::IntermodError() :
    code  (IntermodError::Code::None),
    row   (-1),
    column(-1)
{
    //
}
IntermodError::~IntermodError()
{
    //
}

bool IntermodError::isError() const {
    return code != Code::None;
}
void IntermodError::clear() {
    code   = Code::None;
    row    = -1;
    column = -1;
    message.clear();
}
