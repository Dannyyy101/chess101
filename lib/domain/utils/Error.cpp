//
// Created by Daniel Stöcklein on 03.08.24.
//

#include <utility>

#include "../../../include/domain/utils/Error.h"

Error::Error() : hasError_(false){}

Error::~Error() = default;

void Error::setErrorMessage(std::string errorMessage) {
    std::lock_guard<std::mutex> guard(mutex_);
    this->errorMessage_ = std::move(errorMessage);
    this->hasError_ = true;
}

const std::string Error::getErrorMessage(){
    std::lock_guard<std::mutex> guard(mutex_);
    this->hasError_ = false;
    return this->errorMessage_;
}

void Error::changeError(bool error) {
    std::lock_guard<std::mutex> guard(mutex_);
    this->hasError_ = error;
}

bool Error::hasError() {
    std::lock_guard<std::mutex> guard(mutex_);
    return this->hasError_;
}
