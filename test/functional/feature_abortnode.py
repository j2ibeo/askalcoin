#!/usr/bin/env python3
# Copyright (c) 2019-2020 The Askalcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.
"""Test askalcoind aborts if can't disconnect a block.

- Start a single node and generate 3 blocks.
- Delete the undo data.
- Mine a fork that requires disconnecting the tip.
- Verify that askalcoind AbortNode's.
"""

from test_framework.test_framework import AskalcoinTestFramework
from test_framework.util import get_datadir_path
import os


class AbortNodeTest(AskalcoinTestFramework):
    def set_test_params(self):
        self.setup_clean_chain = True
        self.num_nodes = 2
        self.rpc_timeout = 240

    def setup_network(self):
        self.setup_nodes()
        # We'll connect the nodes later

    def run_test(self):
        self.generate(self.nodes[0], 3)
        datadir = get_datadir_path(self.options.tmpdir, 0)

        # Deleting the undo file will result in reorg failure
        os.unlink(os.path.join(datadir, self.chain, 'blocks', 'rev00000.dat'))

        # Connecting to a node with a more work chain will trigger a reorg
        # attempt.
        self.generate(self.nodes[1], 3)
        with self.nodes[0].assert_debug_log(["Failed to disconnect block"]):
            self.connect_nodes(0, 1)
            self.generate(self.nodes[1], 1)

            # Check that node0 aborted
            self.log.info("Waiting for crash")
            self.nodes[0].wait_until_stopped(timeout=200)
        self.log.info("Node crashed - now verifying restart fails")
        self.nodes[0].assert_start_raises_init_error()


if __name__ == '__main__':
    AbortNodeTest().main()