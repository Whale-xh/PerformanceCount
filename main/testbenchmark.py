from xml.etree.ElementTree import ElementTree
import random
all_benchmarks = ["ackermann",
					"bitops",
					"correlate",
					"crc16",
					"djb2a",
					"euler",
					"explog",
					"fft",
					"fibonacci",
					"float",
					"fnv1a",
					"gcd",
					"hamming",
					"hyperbolic",
					"idct",
					"int",
					"jenkin",
					"jmp",
					"ln2",
					"loop",
					"matrixprod",
					"nsqrt",
					"omega",
					"phi",
					"pi",
					"pjw",
					"prime",
					"psi",
					"queens",
					"sdbm",
					"sqrt",
					"trig",
					"union"]

benchmark_num = len(all_benchmarks)
default_xml = "./Examplebenchmark.xml"

xml_tree = ElementTree()
xml_tree.parse(default_xml)

task_node = xml_tree.findall('tasks')[0]
all_tasks = list(task_node)


path_id = 0
for task in all_tasks:
	task.set('load_type', 'benchmark')
	benchmark_id = random.randint(0, benchmark_num-1)
	benchmark_node = task.find('benchmark')
	benchmark_node.set('name', all_benchmarks[benchmark_id])

xml_tree.write('test_benchmark.xml', encoding="utf-8",xml_declaration=True)