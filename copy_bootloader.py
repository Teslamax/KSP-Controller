import shutil
import os

Import("env")

source = os.path.join("custom_bootloader", "bootloader__80m.elf")
target = os.path.join(env.subst("$BUILD_DIR"), "bootloader__80m.elf")

print("👉 Copying fallback bootloader to build folder...")
if os.path.exists(source):
    shutil.copy(source, target)
    print("✅ bootloader__80m.elf copied successfully.")
else:
    print("❌ bootloader__80m.elf not found in custom_bootloader/")
