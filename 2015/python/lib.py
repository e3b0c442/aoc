def format_duration(seconds: float) -> str:
    labels = ["s", "ms", "µs", "ns"]
    i: int = 0
    for i in range(4):
        if seconds > 1e-3:
            break
        seconds *= 1000
    return f"{seconds:.3f}{labels[i]}"
