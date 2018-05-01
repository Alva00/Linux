# 灰色预测补全2017缺失值
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import PolynomialFeatures
from sklearn.svm import SVR
from sklearn.neural_network import MLPRegressor
from sklearn.neural_network import BernoulliRBM
from sklearn import preprocessing
import matplotlib.pyplot as plt
from scipy import stats
import matplotlib as mpl
import numpy as np
import pandas as pd
import seaborn as sns
import math


def GM(hist_data):
    n = len(hist_data)
    X0 = np.array(hist_data)
    #累加生成
    hist_data_agg = [sum(hist_data[0 : i + 1]) for i in range(n)]
    X1 = np.array(hist_data_agg)
    #计算数据矩阵B和数据向量Y
    B = np.zeros([n - 1, 2])
    Y = np.zeros([n - 1, 1])
    for i in range(0, n - 1):
        B[i][0] = -0.5 * (X1[i] + X1[i + 1])
        B[i][1] = 1
        Y[i][0] = X0[i + 1]
    #计算GM(1,1)微分方程的参数a和u
    A = np.linalg.inv(B.T.dot(B)).dot(B.T).dot(Y)
    a = A[0][0]
    u = A[1][0]
    #建立灰色预测模型
    XX0 = np.zeros(n)
    XX0[0] = X0[0]
    for i in range(1, n):
        XX0[i] = (X0[0] - u/a) * (1 - math.exp(a)) * math.exp(-a * (i))
    #模型精度的后验差检验
    #求残差平均值
    e = 0      
    for i in range(0,n):
        e += (X0[i] - XX0[i])
    e /= n
    #求历史数据平均值
    aver = 0
    for i in range(0,n):
        aver += X0[i]
    aver /= n
    #求历史数据方差
    s12 = 0     
    for i in range(0,n):
        s12 += (X0[i]-aver)**2
    s12 /= n
    #求残差方差
    s22 = 0      
    for i in range(0,n):
        s22 += ((X0[i] - XX0[i]) - e)**2
    s22 /= n
    #求后验差比值
    C = s22 / s12   
    #求小误差概率
    cout = 0
    for i in range(0,n):
        if abs((X0[i] - XX0[i]) - e) < 0.6754*math.sqrt(s12):
            cout = cout+1
        else:
            cout = cout
    P = cout / n

    if (C < 0.35 and P > 0.95):
        #预测精度为一级
        m = 1   #请输入需要预测的年数
        #print('往后m各年负荷为：')
        f = np.zeros(m)
        for i in range(0,m):
            f[i] = (X0[0] - u/a)*(1-math.exp(a))*math.exp(-a*(i+n))  
        print(f)  
    else:
        print('灰色预测法不适用')


def readCSV(filename):
    data = pd.read_csv(filename)
    # 将其转为ndarray
    x_train = data.values[0:9, 1:19]
    y_train = data.values[0:9, 19:21]
    x_test = data.values[9, 1:19]
    '''
    x_train = data.iloc[0:9, 1:21]
    y_train = data.iloc[0:9, 21:23]
    x_test = data.iloc[9, 1:21]
    '''
    return data, x_train, y_train, x_test

def correlation(data):
    x_licks = ['2015-12', '2016-03', '2016-06', '2016-09', '2016-12', '2016-03', '2016-06', '2016-09', '2016-12']
    min_max_scaler = preprocessing.MinMaxScaler()
    newdata = min_max_scaler.fit_transform(data)
    plt.figure(1)
    plt.subplot(241)
    plt.plot(x_licks, newdata['CPI'], 'bo', x_licks, newdata['存款'], 'r--')
    plt.show()
    # print(data.corr()['贷款'])

# 多元线性回归
def multiVariableLinearRegression(x_train, y_train, x_test):
    model = LinearRegression(normalize=True)  
    model.fit(x_train, y_train)  
    y_test = model.predict(x_test.reshape(1, -1))
    print(y_test)

# 多项式回归
def polynomial(x_train, y_train, x_test):
    model = PolynomialFeatures(degree=2)
    x_train_quadratic = model.fit_transform(x_train)
    x_test_quadratic = model.transform(x_test.reshape(1, -1))
    regressor_quadratic = LinearRegression(normalize=True)
    regressor_quadratic.fit(x_train_quadratic, y_train)
    y_test = regressor_quadratic.predict(x_test_quadratic)
    print(y_test)

# 神经网络--垃圾
def neuralnetwork(x_train, y_train, x_test):
    model = MLPRegressor() 
    model.fit(x_train, y_train)  
    y_test = model.predict(x_test.reshape(1, -1))
    print(y_test)

    
if __name__ == "__main__":
    # hist_data0 = [100.89, 101.27, 101.43]
    # hist_data1 = [10.23, 9.50, 7.87]
    # hist_data2 = [4.50, 3.15, -1.09]
    # hist_data3 = [104.5, 104.7, 106.5]
    # hist_data4 = [15.5, 15.31, 13.19]
    # hist_data5 = [93.34, 99.74, 100.69, 100.44, 100.88, 100.89, 101.27, 101.43, 101.59]
    # hist_data6 = [12.36, 13.75, 8.24, 6.72, 6.31, 4.5, 3.15, -1.09, 0]
    # hist_data7 = [1357022, 1411183, 1462397, 1485214, 1505864, 1556487, 1596636, 1622758, 1641044]
    # GM(hist_data0)   #101.59023161
    # GM(hist_data1)   #6.50944145
    # GM(hist_data2)   #0.00061174
    # GM(hist_data3)   #108.32821073
    # GM(hist_data4)   #11.35034035
    # GM(hist_data5)     #101.89534297
    # GM(hist_data6)
    # GM(hist_data7)
    filename = "problem1.csv"
    data, x_train, y_train, x_test = readCSV(filename)
    multiVariableLinearRegression(x_train, y_train, x_test)
    correlation(data)

    

