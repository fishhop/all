#http://www.runoob.com/python/python-variable-types.html
'''
\		例如，“\\n”匹配\n。“\n”匹配换行符。序列“\\”匹配“\”而“\(”则匹配“(”。
\w		[A-Za-z0-9_]
\W		[^A-Za-z0-9_]，不是A-Za-z0-9_中的任何一个
^[A-Z]	以A-Z任意一个字母开头
\d		[0-9]
\D		[^0-9]
^		匹配输入字符串的开始位置
$		匹配输入字符串的结束位置
*		0-N 次
+		>= 1次
?		0-1次，跟在任何一个其他限制符（*,+,?，{n}，{n,}，{n,m}）后面时，匹配模式是非贪婪的。
'''
import re
def string_basic():

	print int('22') + 1 	#23, 转换为数字，默认按照10进制.
	print int('22', 16) 	#34,  按照16进制转换为数字int(x[,base])
	print int('1a', 16) 	#26,  按照16进制转换为数字int(x[,base])

	s = 4321
	print 'str' + str(s) 	#str4321, 转换为字符串

	s = 'abcd'
	print s[-1]				#d
	print s[3]				#d
	print s[::-1], s[::-3]  #dcba da ,从最后一位开始，按步长往前 
	print s[2:]          	#cd 从0计算
	print s[2:3]         	#c, 从0计算,3这里是开区间

	EDIT_NAME = u'保存网页'
	SAVE_NAME = u'保存(&S)'
	ASK_NAME = u'保存网页'
	YES_NAME = u'是(&Y)'

	
def tupple_basic():
	'''
	[]:列表
	()：元组
	{}：字典
	'''
	liebiao = [1, '2', 3, 4]
	print liebiao[1]        #2
	print liebiao[:-1]		#[1, '2', 3]
	print liebiao[::-1] 	#[4, 3, '2', 1]
	print liebiao[::-2]  	#[4, '2']
	print liebiao[::2]      #[1, 3]   
	print liebiao[:2]	    #[1, '2']    
	print liebiao[2:]	    #[3, 4]


	#总结：左闭右开。
	liebiao.append(2)	#为列表追加元素
	
		
	str = "abcd"
	print str[0], str[-1], str[:3]

	yuanzu = (11, '22', 44)#元组 = 只读列表
	print yuanzu[1]	
	tup1 = (12, 34.56);
	tup2 = ('abc', 'xyz');

	# 以下修改元组元素操作是非法的。
	# tup1[0] = 100;

	# 创建一个新的元组
	tup3 = tup1 + tup2;
	print tup3;
	
	
	dict = {} #创建空字典
	zidian = {'shezhen' : 755} 
	zidian['beijing'] = 10

	print zidian # 输出完整的字典
	print zidian.keys() # 输出所有键
	print zidian.values() # 输出所有值
	
	for i in zidian:
		print i, zidian[i], '%d'%zidian[i]
	
def for_func():
	ar = ('aa', 'bb', 'cc')
	for i in ar:
		print i
	print

	
	for i in range(5):
		print i
	print
	
	for i in range(-2, 5, 2):
		print i
	print
	
	str = "changye"
	for i in range(len(str)):
		print str[i]	

def while_func():
	while True:
		inp = raw_input()
		if inp == 'q':
			print 'bye'
			break				#break, 跳出循环
		elif inp == 'ycy':
			print 'haha, clever boy'
		else:
			print inp
		
def func_func(arg = 'shenzhen', val = 2016):
	print val + 1, '@'+arg
	a = 1
	s = 'hah'
	return (a, s) #返回多个值

def try_func():
	try:
		print 'haha'
	except exception, e:
		print e
	else:#无异常才执行
		print 'ok'
	finally:#始终执行
		print 'fin'
		
def class_func():
		
	class Employee:
	   '所有员工的基类'
	   empCount = 0

	   def __init__(self, name, salary):
		  self.name = name
		  self.salary = salary
		  Employee.empCount += 1
	   
	   def displayCount(self):
		 print "Total Employee %d" % Employee.empCount

	   def displayEmployee(self):
		  print "Name : ", self.name,  ", Salary: ", self.salary

	"创建 Employee 类的第一个对象"
	emp1 = Employee("Zara", 2000)
	"创建 Employee 类的第二个对象"
	emp2 = Employee("Manni", 5000)
	emp1.displayEmployee()
	emp2.displayEmployee()
	print "Total Employee %d" % Employee.empCount

def cmtrev():
    dir = ".."
    cmd = 'pwd && ls %s' % ( dir)
    ret = os.system(cmd)	
	
def reg():
	reg = re.compile(r"^[ycy]")		#
	res = reg.findall("yuchangye")
	print res



def reg_reviewer():

	regex = re.compile(r"mailAddress:(.*?);")
	mail_user = regex.findall("mailAddress:123@qq.com;")

	regex = re.compile(r"reviewerA=(.*?);.*?B=(.*?);.*?C=(.*?);")
	reviewer = regex.findall("reviewerA=bob; B=alen; C=divid;")
	reviewerA = reviewer[0][0]
	reviewerB = reviewer[0][1] 
	reviewerC = reviewer[0][2]   
	print reviewerA,reviewerB,reviewerC	

	to_list = ["","",""]
	to_list[0] = reviewerA + '@mycom.net'
	to_list[1] = reviewerB + '@mycom.net'
	to_list[2] = reviewerC + '@mycom.net'

	#首字符不能是_
	#\w = [A-Za-z0-9_]; \W = [^A-Za-z0-9_]; \d = [0-9]; \D = [^0-9]
	print re.findall(r"[a-zA-Z0-9]+[\w\.]*?@\w+\.\w+", "_12sd34_@qq.com,sadf")

def main():
#	string_basic()
#	tupple_basic()
#	while_func()
#	for_func()
#	(a, s) = func_func()
#	print a, s
#	func_func('SZ', 2000)
	class_func()	
#	try_func()
#	reg_reviewer()
#	reg()
	
if __name__ == '__main__':
	main()
