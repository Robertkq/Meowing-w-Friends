#ifndef KQTSUN_MAP
#define KQTSUN_MAP

#include <unordered_map>
#include <mutex>

namespace kq
{
    template<typename Key, typename Value>
    class tsun_map
    {
    public:
        using value_type = std::pair<const Key, Value>;
        using reference = value_type&;
        using mapped_type = Value;

        mapped_type& operator[](const Key& key)
        {
            std::unique_lock lock(m_mutex);
            return m_data[key];
        }
        size_t erase(const Key& key)
        {
            std::unique_lock lock(m_mutex);
            return m_data.erase(key);
        }

        size_t size() const { return m_data.size(); }
        void clear() { m_data.clear(); }

        typename std::unordered_map<Key, Value>::iterator begin()
        {
            return m_data.begin();
        }

        typename std::unordered_map<Key, Value>::iterator end()
        {
            return m_data.end();
        }
    private:
        std::unordered_map<Key, Value> m_data;
        std::mutex m_mutex;
    };
}

#endif