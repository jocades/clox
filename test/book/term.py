none = "\u001b[0m"
reset = "\u001b[39m"


def gray(msg):
    return f"\u001b[1;30m{msg}{none}"


def cyan(msg):
    return f"\u001b[36m{msg}{none}"


def green(msg):
    return f"\u001b[32m{msg}{reset}"


def red(msg):
    return f"\u001b[31m{msg}{reset}"


def yellow(msg):
    return f"\u001b[33m{msg}{reset}"


def pink(msg):
    return f"\u001b[91m{msg}{reset}"
