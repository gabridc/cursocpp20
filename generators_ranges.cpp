#include <generator>
#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include <ranges>

std::generator<std::string> processFile (const std::vector<std::string>& file) {
    for (auto line : file)    
        co_yield line;
}

auto doWork(auto generator, auto&& predicate, auto&& filter) {
    return generator
        | std::views::transform(predicate)
        | std::views::filter(filter);
}

auto stringToOptNumber (const std::string& line) -> std::optional<int> {
    int value = 0;
    if (std::from_chars(line.data(), line.data() + line.size(), value).ec == std::errc{}) {
        return {value};
    }
    return std::nullopt;
}

auto pairOpts(const std::optional<int>& optNumber) -> bool {
    if (optNumber)
        return *optNumber % 2 == 0;
    return false;
}

auto optToNumber(const std::optional<int>& opt) -> int {
    return opt.value();
}

int main() {
    const std::vector<std::string> file = {"123", "456", "1", "aa", "34"};


    for (auto processedLine: processFile(file)
        | std::views::transform(&stringToOptNumber)
        | std::views::filter(&pairOpts) 
        | std::views::transform(&optToNumber))
    {
        std::cout << "Number in line: " << processedLine << std::endl;
    }
}