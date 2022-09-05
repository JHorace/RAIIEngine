//
// Created by James on 8/28/2022.
//

#ifndef RAIIENGINE_I_ENGINE_HPP
#define RAIIENGINE_I_ENGINE_HPP



class IEngine
{
public:
    virtual ~IEngine() {};
    virtual void Render() = 0;
private:
};




#endif //RAIIENGINE_I_ENGINE_HPP
