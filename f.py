def g(n: dict[str, int], m: int) -> dict[str, int]:
    """
    >>> d = {'J': 82, 'A': 46, 'M': 97}
    >>> g(d,50) == {'M': 97, 'J': 82}
    True
    """
    d = {}
    for i in n:
        if n[i] >= m:
            d[i] = m[i]
    return d


if __name__ == '__main__':
    import doctest

    doctest.testmod()