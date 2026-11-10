#include "assignment.h"

#include <utility>

class assignmentData : public QSharedData
{
public:
};

assignment::assignment()
    : data(new assignmentData)
{}

assignment::assignment(const assignment &rhs)
    : data{rhs.data}
{}

assignment::assignment(assignment &&rhs)
    : data{std::move(rhs.data)}
{}

assignment &assignment::operator=(const assignment &rhs)
{
    if (this != &rhs)
        data = rhs.data;
    return *this;
}

assignment &assignment::operator=(assignment &&rhs)
{
    if (this != &rhs)
        data = std::move(rhs.data);
    return *this;
}

assignment::~assignment() = default;
