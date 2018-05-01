# 计算置信区间
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import PolynomialFeatures
from sklearn.svm import SVR
from sklearn.neural_network import MLPRegressor
from sklearn.neural_network import BernoulliRBM
import matplotlib.pyplot as plt
import random
import numpy as np
import pandas as pd
import seaborn as sns
import math

def confidenceInterval(data):
    # 随机抽样
    row = len(data)
    col = len(data[0])
    # 计算每一列的平均值
    mean = np.mean(data, axis=0)
    # 计算每一列的标准差
    std = np.std(data, axis=0)
    # 计算标准误差
    stderror = np.zeros(col)
    for i in range(col):
        stderror[i] = std[i] / math.sqrt(row)
    # 置信水平为９９％，则ｚ值为2.58
    lower = mean - 2.58 * stderror
    upeer = mean + 2.58 * stderror
    return lower, upeer, mean, std


def readCSV(filename, sample_num):
    '''　返回ｎｄａｒｒａｙ　'''
    data = pd.read_csv(filename)

    rows = []
    for i in range(sample_num):
        rows.append(random.randint(0, len(data) - 1))
    return data.values[:, :]


if __name__ == "__main__":
    filename = "problem2.csv"
    # 采样数
    sample_num = 365
    data = readCSV(filename, sample_num)
    lower, upper, mean, std = confidenceInterval(data)
    with open("problem4+answer.csv", 'w+') as file:
        for i  in range(len(upper)):
            file.write("%f, %f, %f, %f\n"%(mean[i], std[i], lower[i], upper[i]))
    file.close()