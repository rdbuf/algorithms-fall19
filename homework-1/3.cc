#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>

int main() {
    std::cin.tie(0);
	std::ios_base::sync_with_stdio(false);

	int v;
	int n;
	std::cin >> v >> n;
	std::vector<std::vector<int>> e(v);
	for (int i = 0; i < n; ++i) {
		int a, b;
		std::cin >> a >> b;
		assert(a < v && b < v);
		e[a].push_back(b);
		e[b].push_back(a);
	}
	int source, target;
	std::cin >> source >> target;

	std::vector<int> cnt(v);
	std::vector<int> locked(v);
	std::unordered_set<int> pending;
	std::unordered_set<int> current;

	current.insert(source);
	cnt[source] = 1;
	locked[source] = true;

	while (!current.empty()) {
		for (int s : current) {
			if (s == target) { goto finish; }
			for (int t : e[s]) {
				if (locked[t]) { continue; }
				cnt[t] += cnt[s];
				pending.insert(t);
			}
		}
		for (int s : pending) { locked[s] = true; }
		current.clear();
		std::swap(current, pending);
	}

finish:
	std::cout << cnt[target] << '\n';
}