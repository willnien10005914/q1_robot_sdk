from setuptools import setup
package_name = "q1_driver"
setup(
    name=package_name,
    version="0.1.0",
    packages=[package_name],
    data_files=[
        ("share/ament_index/resource_index/packages", ["resource/" + package_name]),
        ("share/" + package_name, ["package.xml"]),
    ],
    install_requires=["setuptools"],
    zip_safe=True,
    maintainer="Q1 Team",
    maintainer_email="willnien@gmail.com",
    description="Q1 DDS-ROS bridge",
    license="Apache-2.0",
    entry_points={
        "console_scripts": [
            "q1_driver_node = q1_driver.driver_node:main",
        ],
    },
)
