#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#define BadAlloc \
catch (std::bad_alloc& ba) \
{   \
throw (OutOfMemoryException());    \
}

namespace ColosseumEx {
    
    class ColosseumException : public std::exception {};
    class ElementNotFoundException : public ColosseumException {};
    class OutOfMemoryException : public ColosseumException {};
    class InvalidInputException : public ColosseumException {};
    class ElementAlreadyExistsException : public ColosseumException {};
}




#endif  // EXCEPTIONS_H
