#include <markdownpoint.hpp>

namespace MarkdownPoint
{
    std::vector<std::string> splitString(const std::string &input, split_predicate predicate) {
        std::vector<std::string> result;

        std::string currentInput = input;
        while (currentInput.size() > 0)
        {
            std::string chunk = currentInput.substr(0, predicate(currentInput));
            result.push_back(chunk);
            currentInput = currentInput.substr(chunk.size());
        }

        return result;
    }
}