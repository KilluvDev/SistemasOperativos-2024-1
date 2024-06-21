"""Laboratorio 4."""
from random import sample
from threading import Lock, Condition, Thread
from time import sleep
import logging

logging.basicConfig(level=logging.DEBUG)

class SemaphoreWithOrder:
    """asdf"""
    def __init__(self, value=1):
        if value < 0:
            raise ValueError("semaphore initial value must be >= 0")
        self._cond = Condition(Lock())
        self._value = value

        self._id_queue = []
        self._id_lock = Lock()
        self._id_counter = 0

    def acquire(self):
        """asdf"""
        with self._id_lock:
            current_id = self._id_counter
            self._id_counter += 1
            self._id_queue.append(current_id)

        with self._cond:
            while self._value == 0 or self._id_queue[0] != current_id:
                self._cond.wait()
            self._id_queue.pop(0)
            self._value -= 1

    def release(self):
        """asdf"""
        with self._cond:
            self._value += 1
            self._cond.notify_all()

    __enter__ = acquire

    def __exit__(self, exc_type, exc_value, traceback):
        self.release()

class Island:
    """Island object"""
    name: str
    bridge_capacity: int
    search_duration: int # seconds
    island_capacity: int

    bridge_sem: SemaphoreWithOrder
    island_sem: SemaphoreWithOrder

    island_pass: Condition

    on_bridge: list[int] = []
    on_island: list[int] = []

    def __init__(self, name: str, bridge_capacity: int, search_duration: int, island_capacity: int):
        self.name = name
        self.bridge_capacity = bridge_capacity
        self.search_duration = search_duration
        self.island_capacity = island_capacity

        self.bridge_sem = SemaphoreWithOrder(bridge_capacity)
        self.island_sem = SemaphoreWithOrder(island_capacity)

        self.island_pass = Condition()

    def wait_on_bridge(self, pirate_id: int):
        """Wait on bridge."""
        with self.bridge_sem:
            logging.debug('Pirate %d entered %s bridge', pirate_id, self.name)
            self.on_bridge.append(pirate_id)

            with self.island_pass:
                self.island_pass.notify_all()
                while len(self.on_bridge) < self.island_capacity:
                    self.island_pass.wait()

        logging.debug('Pirate %d went to %s', pirate_id, self.name)

        self.on_bridge.remove(pirate_id)

        with self.island_sem:
            logging.debug('Pirate %d entered %s', pirate_id, self.name)
            self.on_island.append(pirate_id)
            sleep(self.search_duration)
            logging.debug('Pirate %d finished searching on %s', pirate_id, self.name)

        self.on_island.remove(pirate_id)
        with self.island_pass:
            self.island_pass.notify_all()





ISLANDS = [
    # Island('Isla de las Sombras', 20, 9, 10),
    # Island('Isla del Dragón Rojo', 8, 5, 2),
    # Island('Isla de las Estrellas', 15, 7, 5),
    # Island('Isla del Bosque Encantado', 6, 4, 3),
    # Island('Isla de los Susurros', 6, 1, 5),
    # Island('Isla del Trueno', 9, 4, 4),
    # Island('Isla del Tesoro Oculto', 7, 5, 2),
    Island('Isla de pruebas 1', 2, 1, 2),
    Island('Isla de pruebas 2', 2, 1, 2),
]


def debug_islands():
    """Debug islands."""
    while True:
        sleep(5)
        for island in ISLANDS:
            logging.debug('Island %s: %s on bridge, %s on island',
                          island.name,
                          str(island.on_bridge),
                          str(island.on_island))
Thread(target=debug_islands, daemon=True).start()

class Oracle:
    """Oracle bar."""
    _lock = Lock()

    def ask_islands(self) -> list[Island]:
        """Ask for islands."""
        # Only one pirate can ask for islands at a time
        with self._lock:
            logging.debug('Oracle is asked for islands')
            return sample(ISLANDS, 2)

oracle = Oracle()


def run_pirate(pirate_id: int):
    """Run pirate."""
    # 1. Enters oracle bar
    logging.debug('Pirate %d enters the bar', pirate_id)

    # 2. Asks oracle for islands
    logging.debug('Pirate %d asks for islands', pirate_id)
    islands = oracle.ask_islands()

    for island in islands:
        # 3. Goes to the first island or waits for the bridge to have space
        logging.debug('Pirate %d goes to %s', pirate_id, island.name)
        island.wait_on_bridge(pirate_id)


pirates: list[Thread] = []
for i in range(10): # TODO: change to 500
    logging.debug('Creating pirate %d', i)

    pirate = Thread(target=run_pirate, args=(i,))
    pirate.start()
    pirates.append(pirate)

for pirate in pirates:
    pirate.join()
