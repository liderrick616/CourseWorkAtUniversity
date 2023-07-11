"""CSCA08: Fall 2022 -- Assignment 3: Hypertension and Low Income

Starter code.

This code is provided solely for the personal and private use of
students taking the CSC108/CSCA08 course at the University of
Toronto. Copying for purposes other than this use is expressly
prohibited. All forms of distribution of this code, whether as given
or with any changes, are expressly prohibited.

All of the files in this directory and all subdirectories are:
Copyright (c) 2022 Jacqueline Smith, David Liu, and Anya Tafliovich

"""

from typing import TextIO
import statistics

from constants import (CityData, ID, HT, TOTAL, LOW_INCOME,
                       SEP, HT_ID_COL, LI_ID_COL,
                       HT_NBH_NAME_COL, LI_NBH_NAME_COL,
                       HT_20_44_COL, NBH_20_44_COL,
                       HT_45_64_COL, NBH_45_64_COL,
                       HT_65_UP_COL, NBH_65_UP_COL,
                       POP_COL, LI_POP_COL,
                       HT_20_44_IDX, HT_45_64_IDX, HT_65_UP_IDX,
                       NBH_20_44_IDX, NBH_45_64_IDX, NBH_65_UP_IDX
                       )

SAMPLE_DATA = {
    'West Humber-Clairville': {
        'id': 1,
        'hypertension': [703, 13291, 3741, 9663, 3959, 5176],
        'total': 33230, 'low_income': 5950},
    'Mount Olive-Silverstone-Jamestown': {
        'id': 2,
        'hypertension': [789, 12906, 3578, 8815, 2927, 3902],
        'total': 32940, 'low_income': 9690},
    'Thistletown-Beaumond Heights': {
        'id': 3,
        'hypertension': [220, 3631, 1047, 2829, 1349, 1767],
        'total': 10365, 'low_income': 2005},
    'Rexdale-Kipling': {
        'id': 4,
        'hypertension': [201, 3669, 1134, 3229, 1393, 1854],
        'total': 10540, 'low_income': 2140},
    'Elms-Old Rexdale': {
        'id': 5,
        'hypertension': [176, 3353, 1040, 2842, 948, 1322],
        'total': 9460, 'low_income': 2315},
}
SMALL_DATA = {
    'Humble Street': {
        'id': 1,
        'hypertension': [70, 1329, 374, 966, 395, 517],
        'total': 3323, 'low_income': 595},
    'Mountain Street': {
        'id': 2,
        'hypertension': [78, 1290, 357, 881, 292, 390],
        'total': 3294, 'low_income': 969},
    'Thistle Street': {
        'id': 3,
        'hypertension': [22, 363, 104, 282, 134, 176],
        'total': 1036, 'low_income': 200},
    'Oakville Street': {
        'id': 4,
        'hypertension': [13, 271, 99, 302, 183, 247],
        'total': 992, 'low_income': 83},
    'Guildwood Street': {
        'id': 5,
        'hypertension': [135, 2715, 994, 3020, 1832, 2470],
        'total': 9922, 'low_income': 835},
}
EPSILON = 0.005


# This function is provided for use in Task 3. You do not need to
# change it.  Note the use of EPSILON constant (similar to what we had
# in asisgnment 2) for testing.
def get_age_standardized_ht_rate(city_data: CityData, nbh_name: str) -> float:
    """Return the age standardized hypertension rate from the
    neighbourhood in city_data with neighbourhood name nbh_name.

    Precondition: nbh_name is in city_data

    >>> abs(get_age_standardized_ht_rate(SAMPLE_DATA, 'Elms-Old Rexdale') -
    ...     24.44627) < EPSILON
    True
    >>> abs(get_age_standardized_ht_rate(SAMPLE_DATA, 'Rexdale-Kipling') -
    ...     24.72562) < EPSILON
    True

    """

    rates = calculate_ht_rates_by_age_group(city_data, nbh_name)

    # These rates are normalized for only 20+ ages, using the census data
    # that our datasets are based on.
    canada_20_44 = 11_199_830 / 19_735_665  # Number of 20-44 / Number of 20+
    canada_45_64 = 5_365_865 / 19_735_665  # Number of 45-64 / Number of 20+
    canada_65_plus = 3_169_970 / 19_735_665  # Number of 65+ / Number of 20+

    return (rates[0] * canada_20_44 + rates[1] * canada_45_64 +
            rates[2] * canada_65_plus)


def get_hypertension_data(data_type: dict, data_file: TextIO) -> None:
    """Modifies the dictionary data_type by adding and updating the
    Hypertension data from hypertension data file data_file.If
    already exists in data_type, update the newer data to data_type.
    """
    data_file.readline()
    for i in data_file:
        line = i.strip().split(',')
        if line[HT_NBH_NAME_COL] not in data_type:
            data_type[line[HT_NBH_NAME_COL]] = {ID: int(line[HT_ID_COL]),
                                                HT: [int(line[HT_20_44_COL]),
                                                     int(line[NBH_20_44_COL]),
                                                     int(line[HT_45_64_COL]),
                                                     int(line[NBH_45_64_COL]),
                                                     int(line[HT_65_UP_COL]),
                                                     int(line[NBH_65_UP_COL])]}
        else:
            data_type[line[HT_NBH_NAME_COL]][HT] = int(line[0])
            data_type[line[HT_NBH_NAME_COL]][HT] = int(line[1])
            data_type[line[HT_NBH_NAME_COL]][HT] = int(line[2])
            data_type[line[HT_NBH_NAME_COL]][HT] = int(line[3])
            data_type[line[HT_NBH_NAME_COL]][HT] = int(line[4])
            data_type[line[HT_NBH_NAME_COL]][HT] = int(line[5])


def get_low_income_data(data_type: dict, data_file: TextIO) -> None:
    """Modifies the dictionary data_type by adding and updating the
    low-Income data from Low income data file data_file. If already
    exists in data_type, update the newer data to data_type.
    """

    data_file.readline()
    for i in data_file:
        mark = i.strip().split(',')
        if mark[HT_NBH_NAME_COL] not in data_type:
            data_type[mark[LI_NBH_NAME_COL]] = {ID: int(mark[LI_ID_COL]),
                                                TOTAL: int(mark[HT_20_44_COL]),
                                                LOW_INCOME: int(mark[3])}
        else:
            data_type[mark[LI_NBH_NAME_COL]][TOTAL] = int(mark[POP_COL])
            data_type[mark[LI_NBH_NAME_COL]][LOW_INCOME] = \
                int(mark[LI_POP_COL])


def get_bigger_neighbourhood(c_data: CityData, neighbourhood_1: str,
                             neighbourhood_2: str) -> str:
    """return the name of the neighbourhood that has a higher population
    between neighbourhood_1 and neighbourhood_2. If neighbourhood_1 or
    neighbourhood is not in the dictionary c_data, assume the population
    is 0. If neighbourhood_1 population equals neighbourhood_2
    population, return the neighbourhood that appears first in c_data.

    Precondition: population of neighbourhood_1 and neighbourhood_2 is >= 0
    """
    if neighbourhood_1 and neighbourhood_2 not in c_data:
        return neighbourhood_1
    if neighbourhood_1 not in c_data:
        return neighbourhood_2
    if neighbourhood_2 not in c_data:
        return neighbourhood_1
    b_total = c_data[neighbourhood_2][TOTAL]
    a_total = c_data[neighbourhood_1][TOTAL]
    c_id = c_data[neighbourhood_1][ID]
    d_id = c_data[neighbourhood_2][ID]
    if (a_total == b_total and c_id > d_id) or (b_total > a_total):
        return neighbourhood_2
    if (a_total == b_total and c_id < d_id) or (b_total < a_total):
        return neighbourhood_1
    return neighbourhood_1


def get_high_hypertension_rate(hyp_rate_data: CityData, threshold: float) -> \
        list[tuple[str, float]]:
    """return a list of tuples that have all the key/neighbourhood name from
    CityData dictionary hyp_rate_data that has a higher or equal overall
    hypertension rate than the given threshold threshold.

    Precondition: threshold >= 0.0 and <= 1.0
    >>> get_high_hypertension_rate(SAMPLE_DATA, 0.3)
    [('Thistletown-Beaumond Heights', 0.31797739151574084),\
 ('Rexdale-Kipling', 0.3117001828153565)]
    >>> get_high_hypertension_rate(SAMPLE_DATA, 0)
    [('West Humber-Clairville', 0.2987202275151084),\
 ('Mount Olive-Silverstone-Jamestown', 0.28466612028255867),\
 ('Thistletown-Beaumond Heights', 0.31797739151574084),\
 ('Rexdale-Kipling', 0.3117001828153565),\
 ('Elms-Old Rexdale', 0.2878808035120394)]
    >>> get_high_hypertension_rate(SAMPLE_DATA, 1)
    []
    """
    re_turn = []
    for i in hyp_rate_data:
        total_hyp_pop = hyp_rate_data[i][HT][1] + hyp_rate_data[i][HT][3] + \
            hyp_rate_data[i][HT][5]
        total_pop = hyp_rate_data[i][HT][0] + hyp_rate_data[i][HT][2] + \
            hyp_rate_data[i][HT][4]
        hyp_rate = (total_pop / total_hyp_pop)
        if hyp_rate >= threshold:
            re_turn.append((i, hyp_rate))
    return re_turn


def get_ht_to_low_income_ratios(ht_low: CityData) -> dict[str, float]:
    """return a dictionary with the key being the name of all the neighbourhood
    obtained from CityData dictionary ht_low_data and the values being the
    ratio of hypertension rate to the low income rate for each neighbourhood.

    Precondition: all neighbourhood in ht_low_data has a population that is
    greater than 0
    >>> get_ht_to_low_income_ratios(SAMPLE_DATA)
    {'West Humber-Clairville': 1.6683148168616895,\
 'Mount Olive-Silverstone-Jamestown': 0.9676885451091314,\
 'Thistletown-Beaumond Heights': 1.6438083107534431,\
 'Rexdale-Kipling': 1.5351962275111484,\
 'Elms-Old Rexdale': 1.1763941257986577}
    >>> get_ht_to_low_income_ratios(SMALL_DATA)
    {'Humble Street': 1.666326189081607,\
 'Mountain Street': 0.9649940824682697,\
 'Thistle Street': 1.640438489646772,\
 'Oakville Street': 4.2997355274757565,\
 'Guildwood Street': 4.288175677894667}

    """
    ret_urn = {}
    for i in ht_low:
        total_p_op_h_t = ht_low[i][HT][1] + ht_low[i][HT][3] + \
                         ht_low[i][HT][5]
        total_pop_h_t = ht_low[i][HT][0] + ht_low[i][HT][2] + ht_low[i][HT][4]
        total_pop_ht = (total_pop_h_t / total_p_op_h_t)
        total_pop_low = (ht_low[i][LOW_INCOME]) / (ht_low[i][TOTAL])
        total_ = total_pop_ht / total_pop_low
        ret_urn[i] = total_
    return ret_urn


def calculate_ht_rates_by_age_group(ht_rates_data: CityData,
                                    neighbour_name: str) -> \
        tuple[float, float, float]:
    """return a tuple that consists of three data in floats of hypertension
    rate between three age groups in a given neighbourhood
    neighbour_name from CityData dictionary ht_rates_data.

    Precondition: the population of neighbour_name is always greater than 0
    >>> calculate_ht_rates_by_age_group(SAMPLE_DATA, 'Elms-Old Rexdale')
    (5.24903071875932, 36.593947923997185, 71.70953101361573)
    >>> calculate_ht_rates_by_age_group(SAMPLE_DATA, 'Rexdale-Kipling')
    (5.478331970564186, 35.119231960359244, 75.13484358144552)
    >>> calculate_ht_rates_by_age_group(SMALL_DATA, 'Oakville Street')
    (4.797047970479705, 32.78145695364238, 74.08906882591093)

    """
    percent = []
    tup_percent = ()
    rate_ht_20_44 = ((ht_rates_data[neighbour_name][HT][0]) /
                     (ht_rates_data[neighbour_name][HT][1])) * 100
    rate_ht_45_64 = ((ht_rates_data[neighbour_name][HT][2]) /
                     (ht_rates_data[neighbour_name][HT][3])) * 100
    rate_ht_64_up = ((ht_rates_data[neighbour_name][HT][4]) /
                     (ht_rates_data[neighbour_name][HT][5])) * 100
    percent.append(rate_ht_20_44)
    percent.append(rate_ht_45_64)
    percent.append(rate_ht_64_up)
    for i in percent:
        tup_percent = tup_percent + (i,)
    return tup_percent


def get_correlation(correlation_data: CityData) -> float:
    """return a float that is the correlation between age standardised
    hypertension rates and low income rates for all neighbourhoods on
    CityData dictionary correlation_data

    >>> get_correlation(SAMPLE_DATA)
    0.28509539188554994
    >>> get_correlation(SMALL_DATA)
    0.9509500210959325
    """
    correlation_low = []
    cor_relation = []
    for i in correlation_data:
        correlation = 0
        correlation += (correlation_data[i][LOW_INCOME] /
                        correlation_data[i][TOTAL]) * 100
        cor_relation.append(correlation)
    for j in correlation_data:
        low = get_age_standardized_ht_rate(correlation_data, j)
        correlation_low.append(low)
    return statistics.correlation(correlation_low, cor_relation)


def order_by_ht_rate(order_data: CityData) -> list[str]:
    """ return a list with all the names of neighbourhoods in CityData
    dictionary order_data in order of lowest to the highest in terms
    of age-standardised hypertension rate

    Precondition: no hypertension rate is the same
    >>> temp = order_by_ht_rate(SAMPLE_DATA)
    >>> temp == ['Elms-Old Rexdale', 'Rexdale-Kipling',
    ... 'Thistletown-Beaumond Heights','West Humber-Clairville',
    ... 'Mount Olive-Silverstone-Jamestown']
    True
    >>> temp = order_by_ht_rate(SMALL_DATA)
    >>> temp == ['Oakville Street', 'Guildwood Street', 'Thistle Street',
    ... 'Humble Street', 'Mountain Street']
    True
    """
    order = []
    dict_order = {}
    order_final = []
    for i in order_data:
        dict_order[i] = get_age_standardized_ht_rate(order_data, i)
    dict_final = {}
    for m_order in dict_order:
        dict_final[dict_order[m_order]] = m_order
    for k_order in dict_final:
        order.append(k_order)
    list.sort(order)
    for j_order in order:
        order_final.append(dict_final[j_order])
    return order_final


if __name__ == '__main__':
    import doctest

    doctest.testmod()

    # Uncomment when ready to test:
    # Using the small data files:
    small_data = {}
    # add hypertension data
    with open('../a3/hypertension_data_small.csv') as ht_small_f:
        get_hypertension_data(small_data, ht_small_f)
    # add low income data
    with open('../a3/low_income_small.csv') as li_small_f:
        get_low_income_data(small_data, li_small_f)
    print('Did we build the dict correctly?', small_data == SAMPLE_DATA)
    print('Correlation in small data file:', get_correlation(small_data))
    # Using the example data files:
    example_neighbourhood_data = {}
    # add hypertension data
    with open('../a3/hypertension_data_2016.csv') as ht_example_f:
        get_hypertension_data(example_neighbourhood_data, ht_example_f)
    # add low income data
    with open('../a3/low_income_2016.csv') as li_example_f:
        get_low_income_data(example_neighbourhood_data, li_example_f)
    print('Correlation in example data file:',
          get_correlation(example_neighbourhood_data))
