#include "IntermodError.h"


IntermodError::IntermodError() :
    code(IntermodError::Code::None)
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
    code = Code::None;
    message.clear();
}
