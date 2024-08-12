//
// Created by Daniel Stöcklein on 03.08.24.
//

#ifndef CHESS_ERROR_H
#define CHESS_ERROR_H

#include <string>
#include <mutex>

class Error {
private:
    std::string errorMessage_;
    mutable std::mutex mutex_;
public:
    bool hasError_;
    Error();
    ~Error();
    void setErrorMessage(std::string errorMessage);
    const std::string getErrorMessage();
    void changeError(bool error);
    bool hasError();
};


#endif //CHESS_ERROR_H
