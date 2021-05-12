#include "pch.h"
#include "CppUnitTest.h"
#include "../EdmondsKarp/Graph.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestEdmondsKarp
{
	TEST_CLASS(UnitTestEdmondsKarp)
	{
	public:

		TEST_METHOD(TestMethodRead)
		{
			string input_file = "in.txt";
			string output_file = "out.txt";
			string input = "S O 3\nS P 3\nO Q 3\nO P 2\nP R 2\nQ R 4\nQ T 2\nR T 3";
			string expecting_output = "S P 0/3\nS O 0/3\nO P 0/2\nO Q 0/3\nP R 0/2\nQ T 0/2\nQ R 0/4\nR T 0/3\n";
			ofstream out(input_file);
			out << input;
			out.close();
			Graph graph;
			graph.read_from_file(input_file);
			graph.print(output_file);
			ifstream in(output_file);
			string output = "";
			while (in.peek() != EOF)
			{
				char now = in.get();
				output += now;
			}
			in.close();
			Assert::AreEqual(output, expecting_output);
		}

		TEST_METHOD(TestMethodMaxFlow_6_vertexes)
		{
			string input_file = "in.txt";
			string output_file = "out.txt";
			string input = "S O 3\nS P 3\nO Q 3\nO P 2\nP R 2\nQ R 4\nQ T 2\nR T 3";
			string expecting_output = "S P 2/3\nS O 3/3\nO P 0/2\nO Q 3/3\nP R 2/2\nQ T 2/2\nQ R 1/4\nR T 3/3\n";
			ofstream out(input_file);
			out << input;
			out.close();
			Graph graph;
			graph.read_from_file(input_file);
			double max_flow = graph.edmonds_karp();
			graph.print(output_file);
			ifstream in(output_file);
			string output = "";
			while (in.peek() != EOF)
			{
				char now = in.get();
				output += now;
			}
			in.close();
			Assert::AreEqual(output, expecting_output);
			Assert::AreEqual(max_flow, 5.0);
		}
		TEST_METHOD(TestMethodMaxFlow_2_vertexes)
		{
			string input_file = "in.txt";
			string output_file = "out.txt";
			string input = "S T 2";
			string expecting_output = "S T 2/2\n";
			ofstream out(input_file);
			out << input;
			out.close();
			Graph graph;
			graph.read_from_file(input_file);
			double max_flow = graph.edmonds_karp();
			graph.print(output_file);
			ifstream in(output_file);
			string output = "";
			while (in.peek() != EOF)
			{
				char now = in.get();
				output += now;
			}
			in.close();
			Assert::AreEqual(output, expecting_output);
			Assert::AreEqual(max_flow, 2.0);
		}

		TEST_METHOD(TestMethodMaxFlow_3_vertexes)
		{
			string input_file = "in.txt";
			string output_file = "out.txt";
			string input = "S O 1\nO T 4";
			string expecting_output = "S O 1/1\nO T 1/4\n";
			ofstream out(input_file);
			out << input;
			out.close();
			Graph graph;
			graph.read_from_file(input_file);
			double max_flow = graph.edmonds_karp();
			graph.print(output_file);
			ifstream in(output_file);
			string output = "";
			while (in.peek() != EOF)
			{
				char now = in.get();
				output += now;
			}
			in.close();
			Assert::AreEqual(output, expecting_output);
			Assert::AreEqual(max_flow, 1.0);
		}

		TEST_METHOD(TestMethodMaxFlow_triangle)
		{
			string input_file = "in.txt";
			string output_file = "out.txt";
			string input = "S O 2\nO T 1\nS T 3";
			string expecting_output = "S T 3/3\nS O 1/2\nO T 1/1\n";
			ofstream out(input_file);
			out << input;
			out.close();
			Graph graph;
			graph.read_from_file(input_file);
			double max_flow = graph.edmonds_karp();
			graph.print(output_file);
			ifstream in(output_file);
			string output = "";
			while (in.peek() != EOF)
			{
				char now = in.get();
				output += now;
			}
			in.close();
			Assert::AreEqual(output, expecting_output);
			Assert::AreEqual(max_flow, 4.0);
		}

		TEST_METHOD(TestMethodMaxFlow_square)
		{
			string input_file = "in.txt";
			string output_file = "out.txt";
			string input = "S O 2\nO T 1\nS A 2\nA T 3";
			string expecting_output = "S A 2/2\nS O 1/2\nO T 1/1\nA T 2/3\n";
			ofstream out(input_file);
			out << input;
			out.close();
			Graph graph;
			graph.read_from_file(input_file);
			double max_flow = graph.edmonds_karp();
			graph.print(output_file);
			ifstream in(output_file);
			string output = "";
			while (in.peek() != EOF)
			{
				char now = in.get();
				output += now;
			}
			in.close();
			Assert::AreEqual(output, expecting_output);
			Assert::AreEqual(max_flow, 3.0);
		}

		TEST_METHOD(TestMethodMaxFlow_4_vertexes)
		{
			string input_file = "in.txt";
			string output_file = "out.txt";
			string input = "S O 2\nO A 3\nS A 1\nA T 4";
			string expecting_output = "S A 1/1\nS O 2/2\nO A 2/3\nA T 3/4\n";
			ofstream out(input_file);
			out << input;
			out.close();
			Graph graph;
			graph.read_from_file(input_file);
			double max_flow = graph.edmonds_karp();
			graph.print(output_file);
			ifstream in(output_file);
			string output = "";
			while (in.peek() != EOF)
			{
				char now = in.get();
				output += now;
			}
			in.close();
			Assert::AreEqual(output, expecting_output);
			Assert::AreEqual(max_flow, 3.0);
		}

		TEST_METHOD(TestMethodMaxFlow_2_triangles)
		{
			string input_file = "in.txt";
			string output_file = "out.txt";
			string input = "S O 4\nO T 2\nS A 1\nA T 3\nS T 3";
			string expecting_output = "S T 3/3\nS A 1/1\nS O 2/4\nO T 2/2\nA T 1/3\n";
			ofstream out(input_file);
			out << input;
			out.close();
			Graph graph;
			graph.read_from_file(input_file);
			double max_flow = graph.edmonds_karp();
			graph.print(output_file);
			ifstream in(output_file);
			string output = "";
			while (in.peek() != EOF)
			{
				char now = in.get();
				output += now;
			}
			in.close();
			Assert::AreEqual(output, expecting_output);
			Assert::AreEqual(max_flow, 6.0);
		}

		TEST_METHOD(TestMethodMaxFlow_7_vertexes)
		{
			string input_file = "in.txt";
			string output_file = "out.txt";
			string input = "S C 1\nS A 3\nS B 2\nC A 3\nB A 2\nA D 3\nA E 1\nD T 2\nE T 1";
			string expecting_output = "S B 0/2\nS A 3/3\nS C 0/1\nC A 0/3\nA E 1/1\nA D 2/3\nB A 0/2\nD T 2/2\nE T 1/1\n";
			ofstream out(input_file);
			out << input;
			out.close();
			Graph graph;
			graph.read_from_file(input_file);
			double max_flow = graph.edmonds_karp();
			graph.print(output_file);
			ifstream in(output_file);
			string output = "";
			while (in.peek() != EOF)
			{
				char now = in.get();
				output += now;
			}
			in.close();
			Assert::AreEqual(output, expecting_output);
			Assert::AreEqual(max_flow, 3.0);
		}
	};
}
