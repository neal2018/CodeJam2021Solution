import random
import math
import matplotlib.pyplot as plt
import numpy as np
from tqdm import tqdm

NUM = 100
Q_NUM = 10000
CHEAT_PROBABILITY = 0.5
MIN = -3
MAX = 3


def generate(p_ability=None, q_difficulty=None, is_cheater=False):
    """
    generate answers from NUM players with given parameters
    with Q_NUM questions
    """
    if q_difficulty is None:
        q_difficulty = np.random.rand(Q_NUM) * (MAX - MIN) + MIN
    if p_ability is None:
        p_ability = np.random.rand(NUM) * (MAX - MIN) + MIN
        
    answer = np.zeros((NUM, Q_NUM))
    for i in tqdm(range(NUM)):
        for j in range(Q_NUM):
            p = 1 / (1 + math.exp(q_difficulty[j] - p_ability[i]))
            if is_cheater and random.random() < CHEAT_PROBABILITY:
                answer[i][j] += 1
            elif random.random() < p:
                answer[i][j] += 1
    return answer


def get_index(answer, player_mean, question_mean):
    index = [0 for _ in range(NUM)]
    for i in tqdm(range(NUM)):
        for j in range(Q_NUM):
            # modify here to explore other possibilities
            if player_mean[i] > CHEAT_PROBABILITY:
                if answer[i][j] == 0:
                    index[i] += (question_mean[j])**4 / ((1 - player_mean[i])**2)
    return index


if __name__ == "__main__":
    # simulate the distribution of the index

    q_difficulty = np.random.rand(Q_NUM) * (MAX - MIN) + MIN
    answer = generate(q_difficulty=q_difficulty)
    answer_cheater = generate(q_difficulty=q_difficulty, is_cheater=True)

    question_mean = [sum(answer[i][j] for i in range(NUM)) / NUM for j in range(Q_NUM)]
    player_mean = [sum(answer[i]) / Q_NUM for i in range(NUM)]
    index = get_index(answer, player_mean, question_mean)

    cheater_mean = [sum(answer_cheater[i]) / Q_NUM for i in range(NUM)]
    cheater_index = get_index(answer_cheater, cheater_mean, question_mean)
    
    bins = np.linspace(0, max(max(index), max(cheater_index)), 100)
    plt.hist(index, bins, alpha=0.5, label="normal")
    plt.hist(cheater_index, bins, alpha=0.5, label="cheating")
    plt.legend(loc='upper right')
    plt.show()
