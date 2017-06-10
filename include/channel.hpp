#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

template <class T>
class Channel {
private:
    using Pointer = T *;
    Pointer *data_;
    size_t sz_, cap_;
    std::atomic<bool> done_;
    std::mutex mx_;
    std::condition_variable has_data_;
    std::condition_variable not_full_;
public:
    Channel(size_t c)
        :
        done_(false)
        , sz_(0)
        , cap_(c) {
        data_ = new Pointer[c];
    }

    ~Channel() {
        delete[] data_;
    }

    Channel(const Channel&) = delete;

    Channel& operator=(const Channel&) = delete;

    friend void operator<<(Channel<T>& ch, T& t) {
        std::unique_lock<std::mutex> lk{ch.mx_};
        while (ch.sz_ == ch.cap_) {
            /* wait until data is consumed */
            ch.not_full_.wait(lk);
        }
        ch.data_[ch.sz_++] = &t;
        lk.unlock();
        ch.has_data_.notify_one();
    }

    friend bool operator>>(Channel<T>& ch, T& t) {
        std::unique_lock<std::mutex> lk{ch.mx_};
        while (ch.sz_ == 0 && !ch.done_.load()) {
            ch.has_data_.wait(lk, [&]() -> bool {
                return ch.sz_ > 0 || ch.done_.load();
            });
        }
        if (ch.done_.load()) return false;
        t = *(ch.data_[--ch.sz_]);
        lk.unlock();
        ch.not_full_.notify_one();
        return true;
    }

    void Close();

    bool IsClosed();
};

template <class T>
void Channel<T>::Close() {
    done_ = true;
    has_data_.notify_all();
}

template <class T>
bool Channel<T>::IsClosed() {
    return done_.load();
}

#if 0
using namespace std;
int main() {
    Channel<int> chan(10);
    int numConsumer = 1;
    int numData = 1000;
    int *input = new int[numData];
    int *output = new int[numData];

    for (int i = 0; i < numData; i++) {
        input[i] = i;
    }

    vector<thread> consumers(numConsumer);

    /* start consumers first */
    for (int i = 0; i < numConsumer; ++i) {
        consumers[i] = thread{[&]() {
            int k;
            while (chan >> k) {
                output[k] = k;
            }
        }};
    }

    /* then begin producing */
    for (int i = 0; i < numData; ++i) {
        chan << input[i];
    }
    cerr << "Done with producing\n";
    /* when data is done, close the channel */
    chan.Close();
    cerr << "Done with closing\n";
    /* wait until consumer is done */
    for (auto& t: consumers) {
        if (t.joinable()) t.join();
    }

    /* show data */
    for (int i = 0; i < numData; ++i) {
        cerr << output[i] << endl;
    }

    delete[] input;
    delete[] output;
}
#endif