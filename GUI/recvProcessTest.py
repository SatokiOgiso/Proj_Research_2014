# -*- coding: cp932 -*-
import recvProcess
import unittest

class TestRecvProcess(unittest.TestCase):
    #���ʂ̃f�[�^�����DA�ɑ����l��Ԃ�
    def testData1(self):
        obtained_char = 'A1\n'
        e_obtained = recvProcess.parseData()
        e_expected = 1
        self.assertEqual(e_obtained, e_expected)

    def testData100(self):
        obtained_char = 'A100\n'
        e_obtained = recvProcess.parseData()
        e_expected = 100
        self.assertEqual(e_obtained, e_expected)

    def testData200(self):
        obtained_char = 'A200\n'
        e_obtained = recvProcess.parseData()
        e_expected = 200
        self.assertEqual(e_obtained, e_expected)
        
    def testData1000(self):
        obtained_char = 'A1000\n'
        e_obtained = recvProcess.parseData()
        e_expected = 1000
        self.assertEqual(e_obtained, e_expected)

    #���肦�Ȃ��l�����D�󃊃X�g [] ��Ԃ�
    def testData_miss1(self):
        obtained_char = 'B1000\n'
        e_obtained = recvProcess.parseData()
        e_expected = []
        self.assertEqual(e_obtained, e_expected)
        
    def testData_miss2(self):
        obtained_char = 'A10000\n'
        e_obtained = recvProcess.parseData()
        e_expected = []
        self.assertEqual(e_obtained, e_expected)

    def testData_miss3(self):
        obtained_char = 'A\n'
        e_obtained = recvProcess.parseData()
        e_expected = []
        self.assertEqual(e_obtained, e_expected)

    def testData_miss4(self):
        obtained_char = 'A100' #���s���Ȃ��ꍇ
        e_obtained = recvProcess.parseData()
        e_expected = []
        self.assertEqual(e_obtained, e_expected)
        
    def testData_miss5(self):
        obtained_char = '' 
        e_obtained = recvProcess.parseData()
        e_expected = []
        self.assertEqual(e_obtained, e_expected)
        
    def testData_miss6(self):
        obtained_char = '1r0ff' #�s���Ȓl����
        e_obtained = recvProcess.parseData()
        e_expected = []
        self.assertEqual(e_obtained, e_expected)


if __name__ == '__main__':
    unittest.main()
