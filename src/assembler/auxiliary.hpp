
template<typename T>
std::string to_string(const std::vector<T> &vector) {
    std::string str{};

    if (vector.size() == 1) {
        str += to_string(vector[0]);
    } else if (vector.size() > 1) {
        for (size_t i = 0; i < vector.size() - 1; ++i) {
            str += to_string(vector[i]) + ", ";
        }

        str += "or " + to_string(vector[vector.size() - 1]);
    }

    return str;
}