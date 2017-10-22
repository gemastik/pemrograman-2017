#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

const int QUERY_ADD = 1;
const int QUERY_REMOVE = 2;
const int MIN_X = 1;
const int MAX_X = 1000 * 1000 * 1000;
const int MIN_K = 1;
const int MAX_K = 1000 * 1000 * 1000;
const int MAX_N = 5e4;

class ProblemSpec : public BaseProblemSpec {
protected:
	int T;

	int N;
	vector<vector<int>> queries; // <type, xmin, xmax, k>

	vector<int> res;

	void InputFormat() {
		LINE(N);
		LINES(queries) % SIZE(N);
	}

	void OutputFormat() {
		LINES(res) % SIZE(N);
	}

	void GradingConfig() {
		TimeLimit(10);
		MemoryLimit(512);
	}

	void MultipleTestCasesConfig() {
		Counter(T);
	}

	void MultipleTestCasesConstraints() {
		CONS(1 <= T && T <= 10);
	}

	void Constraints() {
		CONS(1 <= N && N <= MAX_N);
	}

	void Subtask1() {
		CONS(validQueries(true));
	}

	void Subtask2() {
		CONS(validQueries());
	}

private:
	bool validQueries(bool easy = false) {
		if (queries.size() != N) return false;

		for (int i = 0; i < queries.size(); i++) {
			if (queries.size() < 1) return false;

			int type = queries[i][0];
			if ((type == QUERY_ADD) || (type == QUERY_REMOVE)) {
				if (queries[i].size() != 4) return false;
				int xMin = queries[i][1];
				int xMax = queries[i][2];
				int k = queries[i][3];

				if (xMin > xMax) return false;
				if (xMin < MIN_X) return false;
				if (xMax > MAX_X) return false;
				if (easy && xMin != xMax) return false;

				if (k < MIN_K || k > MAX_K) return false;
			} else {
				// Invalid type
				return false;
			}
		}
		return true;
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
	void BeforeTestCase() {
		queries.clear();
	}

	void SampleTestCase1() {
		Subtasks({1, 2});
		Input({
			"4",
			"1 1 1 1",
			"1 3 3 2",
			"1 2 2 1",
			"2 1 1 1"
		});
		Output({
			"2",
			"2",
			"4",
			"1"
		});
	}

	void SampleTestCase2() {
		Subtasks({2});
		Input({
			"4",
			"1 1 5 2",
			"1 11 15 1",
			"1 6 10 2",
			"2 1 15 1"
		});
		Output({
			"6",
			"6",
			"16",
			"11"
		});
	}

	void TestGroup1() {
		Subtasks({1, 2});

		// Only add 1 -> MAX_N_SMALL
		CASE(N = MAX_N, linearOne("asc", MIN_K, MAX_K));
		CASE(N = MAX_N, linearOne("desc", MIN_K, MAX_K));
		CASE(N = MAX_N, linearOne("random", MIN_K, MAX_K));

		// spam(remove_rate, spam_range)
		CASE(N = MAX_N, spam(40, 100, MAX_K, MAX_K));
		CASE(N = MAX_N, spam(30, 50, MAX_K, MAX_K));
		CASE(N = MAX_N, spam(60, 1, MIN_K, MAX_K)); // 0/1

		CASE(N = MAX_N, upperAddRemove(20 * 1000, 19 * 1000, 20 * 1000, MAX_K, MAX_K));
		CASE(N = MAX_N, upperAddRemove(30 * 1000, 25 * 1000, 30 * 1000, MAX_K, MAX_K));
		CASE(N = MAX_N, upperAddRemove(20 * 1000, 19 * 1000, 30 * 1000, MAX_K - 5, MAX_K));
		// to have some bigger value
		CASE(N = MAX_N, random(MIN_X, MAX_X, MAX_K, MAX_K));
	}

	void TestGroup2() {
		Subtasks({2});
		CASE(N = MAX_N, linearS(MAX_X / (2 * N), "asc", MIN_K, MAX_K));
		CASE(N = MAX_N, linearS(MAX_X / (N + 1), "random", MIN_K, MAX_K));

		CASE(N = MAX_N, addRemove(MAX_K, MAX_K));

		CASE(N = MAX_N, randomChunks(sqrt(MAX_X), 3, 10));
		CASE(N = MAX_N, randomChunks(sqrt(N), 5, 7));
		CASE(N = MAX_N, randomChunks(3 * sqrt(N), MIN_K, MAX_K));
		CASE(N = MAX_N, randomChunks(N, 1, 4));

		CASE(N = MAX_N, leftPaddedSegments(30, 100, 120));
		CASE(N = MAX_N, leftPaddedSegments(60, 15, 50));
		CASE(N = MAX_N, leftPaddedSegments(35, MAX_K >> 1, MAX_K));
	}

private:
	// literally random
	void random(int min_x, int max_x, int min_k, int max_k) {
		for (int i = 0; i < N; ++i) {
			int x = rnd.nextInt(min_x, max_x);
			queries.push_back({rnd.nextInt(QUERY_ADD, QUERY_REMOVE), x, x, rnd.nextInt(min_k, max_k)});
		}
	}

	// spam in [1, range]
	void spam(int removePercentage, int range, int min_k, int max_k) {
		for (int i = 0; i < N; ++i) {
			int x = rnd.nextInt(1, range);
			queries.push_back({rnd.nextInt(1, 100) <= removePercentage ? QUERY_REMOVE : QUERY_ADD, x, x, rnd.nextInt(min_k, max_k)});
		}
	}

	void upperAddRemove(int base, int lo, int hi, int min_k, int max_k) {
		for (int i = 1; i <= base; ++i) {
			queries.push_back({QUERY_ADD, i, i, rnd.nextInt(min_k, max_k)});
		}
		while (queries.size() + 2 <= N) {
			int x = rnd.nextInt(lo, hi);
			queries.push_back({QUERY_REMOVE, x, x, rnd.nextInt(min_k, max_k)});
			queries.push_back({QUERY_ADD, x, x, rnd.nextInt(min_k, max_k)});
		}
		while (queries.size() < N) {
			int x = rnd.nextInt(lo, hi);
			queries.push_back({QUERY_REMOVE, x, x, rnd.nextInt(min_k, max_k)});
		}
	}

	// alternating between add and remove of same blocks
	void addRemove(int min_k, int max_k) {
		queries.push_back({QUERY_ADD, MIN_X, MAX_X, rnd.nextInt(min_k, max_k)});
		for (int i = 1; i + 2 < N; i += 2) {
			int l = rnd.nextInt(MIN_X, MAX_X);
			int r = rnd.nextInt(l, MAX_X);
			queries.push_back({QUERY_REMOVE, l, r, rnd.nextInt(min_k, max_k)});
			queries.push_back({QUERY_ADD, l, r, rnd.nextInt(min_k, max_k)});
		}
		if (N % 2 == 0) {
			queries.push_back({QUERY_REMOVE, rnd.nextInt(1, MAX_X / 2), rnd.nextInt(MAX_X / 2 + 1, MAX_X), rnd.nextInt(min_k, max_k)});
		}
	}

	// addRemove only for small constraint
	void addRemoveOne(int range) {
		int i = 1;
		for (; i <= range; ++i) {
			queries.push_back({QUERY_ADD, i, i, 1});
		}
		for (; i + 2 <= N; i += 2) {
			int x = rnd.nextInt(1, range);
			queries.push_back({QUERY_REMOVE, x, x, 1});
			queries.push_back({QUERY_ADD, x, x, 1});
		}
		if (queries.size() < N) {
			int x = rnd.nextInt(1, range);
			queries.push_back({QUERY_REMOVE, x, x, 1});
		}
	}

	// randomized fixed-sized chunks
	void randomChunks(int chunkSize, int min_k, int max_k) {
		queries.push_back({QUERY_REMOVE, MIN_X, MAX_X, max_k}); // dummy remove
		queries.push_back({QUERY_ADD, MIN_X, rnd.nextInt(MAX_X >> 1, MAX_X), max_k}); // base
		for (int i = 2; i < N; ++i) {
			int l = rnd.nextInt(1, MAX_X - chunkSize);
			queries.push_back({rnd.nextInt(QUERY_ADD, QUERY_REMOVE), l, l + chunkSize - 1, rnd.nextInt(min_k, max_k)});
		}
	}

	// higher chance to have different answer for each update
	void leftPaddedSegments(int removePercentage, int min_k, int max_k) {
		for (int i = 0; i < N; ++i) {
			int r = rnd.nextInt(MIN_X, MAX_X);
			queries.push_back({rnd.nextInt(1, 100) <= removePercentage ? QUERY_REMOVE : QUERY_ADD, 1, r, rnd.nextInt(min_k, max_k)});
		}
	}

	// only add segments of size K (asc or desc)
	void linearS(int K, string order, int min_k, int max_k) {
		int start = 1;
		for (int i = 0; i < N; ++i) {
			queries.push_back(vector<int>({QUERY_ADD, start, start + K - 1, rnd.nextInt(min_k, max_k)}));
			start += K;
		}
		if (order == "desc") {
			reverse(queries.begin(), queries.end());
		} else if (order == "random") {
			rnd.shuffle(queries.begin(), queries.end());
		}
	}

	void linearOne(string order, int min_k, int max_k) {
		linearS(1, order, min_k, max_k);
	}
};
