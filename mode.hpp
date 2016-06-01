#ifndef MODE_HPP
#define MODE_HPP

#include <string>

class Mode
{
    std::string name; ///< Mode's name
    int priority;     ///< Mode's priority used for storing the Mode in a specific priority group in the priority map. Default: 0
  public:
    Mode();
    ///
    /// \brief Mode
    /// \param name Mode's name
    /// \param priority Mode's priority used for storing the Mode in a specific priority group in the priority map. Default: 0
    ///
    Mode(const std::string &name, const int priority=0);
    virtual ~Mode();

    std::string getName() const;
    void setName(const std::string &value);

    int getPriority() const;
    void setPriority(int value);

    ///
    /// \brief run is the part of a Mode which is executed by the ModeExecutor
    ///
    virtual void run() = 0;
};

class ModeSleep : public Mode
{
    unsigned int ms; ///< Number of microseconds the Mode will sleep for
  public:
    ModeSleep();
    ///
    /// \brief ModeSleep
    /// \param name Mode's name
    /// \param priority Mode's priority used for storing the Mode in a specific priority group in the priority map. Default: 0
    /// \param ms Number of microseconds the Mode will sleep for
    ///
    ModeSleep(const std::string &name, const int priority, const unsigned int ms);
    ~ModeSleep();

    unsigned int getMilliseconds() const;
    void setMicroseconds(unsigned int ms);

    virtual void run() override;
};

class ModeFactorial : public Mode
{
    unsigned int value;   ///< Value for the calculation of the factorial
    unsigned int result;  ///< Calculated factorial based on the given value
  public:
    ModeFactorial();
    ///
    /// \brief ModeFactorial
    /// \param name Mode's name
    /// \param priority Mode's priority used for storing the Mode in a specific priority group in the priority map. Default: 0
    /// \param value Value for the calculation of the factorial
    ///
    ModeFactorial(const std::string &name, const int priority, const unsigned int value);
    ~ModeFactorial();

    unsigned int getResult() const;
    void setValue(unsigned int value);

    virtual void run() override;
};

#endif // MODE_HPP
