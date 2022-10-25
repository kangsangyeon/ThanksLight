#pragma once

#define DECLARE_SINGLETON_CLASS(TClass) \
    public: \
        static TClass Instance; \
    protected: \
        TClass(); \
        virtual ~TClass(); \
    private: \
        TClass(const TClass& _instance) = default; \
        TClass& operator=(const TClass& _instance) {}

#define DEFINE_SINGLETON_CLASS(TClass) \
        TClass TClass::Instance;
