#include "MainForm.h"

using namespace EncryptionTool;

// Initialize encryption when algorithm changes
void MainForm::InitializeEncryption()
{
    // Populate algorithm combo box
    if (comboBox1->Items->Count == 0)
    {
        for each(String ^ algo in encryptionAlgorithms)
        {
            comboBox1->Items->Add(algo);
        }
        comboBox1->SelectedIndex = 0;
    }

    UpdateKeySizes();

    int keySizeBytes = GetKeySizeInBytes();
    key = GenerateRandomKey(keySizeBytes);

    // Set appropriate IV size based on algorithm
    int ivSize = 16; // Default 128-bit IV
    String^ algorithm = comboBox1->SelectedItem->ToString();
    if (algorithm == "ChaCha20")
    {
        ivSize = 12; // 96-bit nonce for ChaCha20
    }

    iv = GenerateRandomIV(ivSize);

    label4->Text = "Key: " + comboBox2->SelectedItem->ToString() + " - " + key;

    if (algorithm == "ChaCha20")
    {
        label5->Text = "Nonce (96 bit): " + iv;
    }
    else if (algorithm == "RC4")
    {
        label5->Text = "IV: Not used for RC4";
    }
    else
    {
        label5->Text = "IV (128 bit): " + iv;
    }
}

void MainForm::UpdateKeySizes()
{
    comboBox2->Items->Clear();
    String^ algorithm = comboBox1->SelectedItem->ToString();

    if (algorithm == "AES")
    {
        comboBox2->Items->Add("128 bit (16 bytes)");
        comboBox2->Items->Add("192 bit (24 bytes)");
        comboBox2->Items->Add("256 bit (32 bytes)");
        comboBox2->SelectedIndex = 2;
    }
    else if (algorithm == "RC4")
    {
        comboBox2->Items->Add("40 bit (5 bytes) - Weak");
        comboBox2->Items->Add("56 bit (7 bytes) - Weak");
        comboBox2->Items->Add("64 bit (8 bytes)");
        comboBox2->Items->Add("128 bit (16 bytes)");
        comboBox2->Items->Add("256 bit (32 bytes)");
        comboBox2->SelectedIndex = 3;
    }
    else if (algorithm == "ChaCha20")
    {
        comboBox2->Items->Add("128 bit (16 bytes)");
        comboBox2->Items->Add("256 bit (32 bytes)");
        comboBox2->SelectedIndex = 1;
    }
    else if (algorithm == "Blowfish")
    {
        comboBox2->Items->Add("32 bit (4 bytes) - Very Weak");
        comboBox2->Items->Add("64 bit (8 bytes) - Weak");
        comboBox2->Items->Add("128 bit (16 bytes)");
        comboBox2->Items->Add("192 bit (24 bytes)");
        comboBox2->Items->Add("256 bit (32 bytes)");
        comboBox2->Items->Add("448 bit (56 bytes) - Maximum");
        comboBox2->SelectedIndex = 4;
    }
    else if (algorithm == "3DES")
    {
        comboBox2->Items->Add("112 bit (14 bytes) - 2-key");
        comboBox2->Items->Add("168 bit (21 bytes) - 3-key");
        comboBox2->SelectedIndex = 1;
    }
}

int MainForm::GetKeySizeInBytes()
{
    String^ keySizeText = comboBox2->SelectedItem->ToString();

    if (keySizeText->Contains("56 bytes")) return 56;
    if (keySizeText->Contains("32 bytes")) return 32;
    if (keySizeText->Contains("24 bytes")) return 24;
    if (keySizeText->Contains("21 bytes")) return 21;
    if (keySizeText->Contains("16 bytes")) return 16;
    if (keySizeText->Contains("14 bytes")) return 14;
    if (keySizeText->Contains("8 bytes")) return 8;
    if (keySizeText->Contains("7 bytes")) return 7;
    if (keySizeText->Contains("5 bytes")) return 5;
    if (keySizeText->Contains("4 bytes")) return 4;

    return 16; // Default
}

String^ MainForm::GenerateRandomKey(int size)
{
    array<Byte>^ randomBytes = gcnew array<Byte>(size);
    RNGCryptoServiceProvider^ rng = gcnew RNGCryptoServiceProvider();
    rng->GetBytes(randomBytes);
    return Convert::ToBase64String(randomBytes);
}

String^ MainForm::GenerateRandomIV(int size)
{
    array<Byte>^ randomBytes = gcnew array<Byte>(size);
    RNGCryptoServiceProvider^ rng = gcnew RNGCryptoServiceProvider();
    rng->GetBytes(randomBytes);
    return Convert::ToBase64String(randomBytes);
}

// Event Handlers
void MainForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        String^ plainText = textBox1->Text;
        String^ algorithm = comboBox1->SelectedItem->ToString();

        if (String::IsNullOrEmpty(plainText) || plainText == "Enter your text here...")
        {
            MessageBox::Show(L"Please enter text to encrypt.");
            return;
        }

        String^ encryptedText = EncryptString(plainText, algorithm);
        richTextBox1->Text = "ENCRYPTED TEXT (" + algorithm + " - " + comboBox2->SelectedItem->ToString() + "):\r\n" + encryptedText;
        richTextBox1->ForeColor = Color::DarkGreen;
    }
    catch (Exception^ ex)
    {
        MessageBox::Show("Encryption failed: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

void MainForm::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        String^ cipherText = textBox1->Text;
        String^ algorithm = comboBox1->SelectedItem->ToString();

        if (String::IsNullOrEmpty(cipherText) || cipherText == "Enter your text here...")
        {
            MessageBox::Show(L"Please enter text to decrypt.");
            return;
        }

        String^ decryptedText = DecryptString(cipherText, algorithm);
        richTextBox1->Text = "DECRYPTED TEXT (" + algorithm + " - " + comboBox2->SelectedItem->ToString() + "):\r\n" + decryptedText;
        richTextBox1->ForeColor = Color::DarkBlue;
    }
    catch (Exception^ ex)
    {
        MessageBox::Show("Decryption failed: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

void MainForm::button3_Click(System::Object^ sender, System::EventArgs^ e)
{
    OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
    openFileDialog->Filter = "All files (*.*)|*.*";
    openFileDialog->Title = "Select file to encrypt/decrypt";
    if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
    {
        textBox2->Text = openFileDialog->FileName;
    }
}

void MainForm::button4_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        String^ inputFile = textBox2->Text;
        String^ algorithm = comboBox1->SelectedItem->ToString();

        if (String::IsNullOrEmpty(inputFile) || !File::Exists(inputFile) || inputFile == "Select a file...")
        {
            MessageBox::Show(L"Please select a valid file to encrypt.");
            return;
        }

        String^ outputFile = Path::Combine(Path::GetDirectoryName(inputFile),
            Path::GetFileNameWithoutExtension(inputFile) + "_encrypted" + Path::GetExtension(inputFile));

        if (EncryptFile(inputFile, outputFile, algorithm))
        {
            richTextBox1->Text = "FILE ENCRYPTED SUCCESSFULLY!\r\nAlgorithm: " + algorithm +
                " (" + comboBox2->SelectedItem->ToString() + ")\r\nInput: " + inputFile + "\r\nOutput: " + outputFile;
            richTextBox1->ForeColor = Color::DarkGreen;
        }
        else
        {
            MessageBox::Show(L"File encryption failed.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
    catch (Exception^ ex)
    {
        MessageBox::Show("File encryption failed: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

void MainForm::button5_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        String^ inputFile = textBox2->Text;
        String^ algorithm = comboBox1->SelectedItem->ToString();

        if (String::IsNullOrEmpty(inputFile) || !File::Exists(inputFile) || inputFile == "Select a file...")
        {
            MessageBox::Show(L"Please select a valid file to decrypt.");
            return;
        }

        String^ outputFile = Path::Combine(Path::GetDirectoryName(inputFile),
            Path::GetFileNameWithoutExtension(inputFile) + "_decrypted" + Path::GetExtension(inputFile));

        if (DecryptFile(inputFile, outputFile, algorithm))
        {
            richTextBox1->Text = "FILE DECRYPTED SUCCESSFULLY!\r\nAlgorithm: " + algorithm +
                " (" + comboBox2->SelectedItem->ToString() + ")\r\nInput: " + inputFile + "\r\nOutput: " + outputFile;
            richTextBox1->ForeColor = Color::DarkBlue;
        }
        else
        {
            MessageBox::Show(L"File decryption failed.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
    catch (Exception^ ex)
    {
        MessageBox::Show("File decryption failed: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

void MainForm::comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
    UpdateKeySizes();
    InitializeEncryption();
}

// Encryption Methods
String^ MainForm::EncryptString(String^ plainText, String^ algorithm)
{
    array<Byte>^ plainBytes = Encoding::UTF8->GetBytes(plainText);
    array<Byte>^ keyBytes = Convert::FromBase64String(key);
    array<Byte>^ ivBytes = Convert::FromBase64String(iv);
    array<Byte>^ encryptedBytes;

    if (algorithm == "AES")
    {
        encryptedBytes = AES_Encrypt(plainBytes, keyBytes, ivBytes);
    }
    else if (algorithm == "RC4")
    {
        encryptedBytes = RC4_Encrypt(plainBytes, keyBytes);
    }
    else if (algorithm == "ChaCha20")
    {
        array<Byte>^ nonce = gcnew array<Byte>(12);
        Array::Copy(ivBytes, nonce, 12);
        encryptedBytes = ChaCha20_Encrypt(plainBytes, keyBytes, nonce);
    }
    else if (algorithm == "3DES")
    {
        encryptedBytes = TripleDES_Encrypt(plainBytes, keyBytes, ivBytes);
    }
    else if (algorithm == "Blowfish")
    {
        encryptedBytes = Blowfish_Encrypt(plainBytes, keyBytes, ivBytes);
    }
    else
    {
        throw gcnew ArgumentException("Unsupported algorithm: " + algorithm);
    }

    return Convert::ToBase64String(encryptedBytes);
}

String^ MainForm::DecryptString(String^ cipherText, String^ algorithm)
{
    array<Byte>^ cipherBytes = Convert::FromBase64String(cipherText);
    array<Byte>^ keyBytes = Convert::FromBase64String(key);
    array<Byte>^ ivBytes = Convert::FromBase64String(iv);
    array<Byte>^ decryptedBytes;

    if (algorithm == "AES")
    {
        decryptedBytes = AES_Decrypt(cipherBytes, keyBytes, ivBytes);
    }
    else if (algorithm == "RC4")
    {
        decryptedBytes = RC4_Decrypt(cipherBytes, keyBytes);
    }
    else if (algorithm == "ChaCha20")
    {
        array<Byte>^ nonce = gcnew array<Byte>(12);
        Array::Copy(ivBytes, nonce, 12);
        decryptedBytes = ChaCha20_Decrypt(cipherBytes, keyBytes, nonce);
    }
    else if (algorithm == "3DES")
    {
        decryptedBytes = TripleDES_Decrypt(cipherBytes, keyBytes, ivBytes);
    }
    else if (algorithm == "Blowfish")
    {
        decryptedBytes = Blowfish_Decrypt(cipherBytes, keyBytes, ivBytes);
    }
    else
    {
        throw gcnew ArgumentException("Unsupported algorithm: " + algorithm);
    }

    return Encoding::UTF8->GetString(decryptedBytes);
}

bool MainForm::EncryptFile(String^ inputFile, String^ outputFile, String^ algorithm)
{
    try
    {
        array<Byte>^ fileData = File::ReadAllBytes(inputFile);
        array<Byte>^ keyBytes = Convert::FromBase64String(key);
        array<Byte>^ ivBytes = Convert::FromBase64String(iv);
        array<Byte>^ encryptedData;

        if (algorithm == "AES")
        {
            encryptedData = AES_Encrypt(fileData, keyBytes, ivBytes);
        }
        else if (algorithm == "RC4")
        {
            encryptedData = RC4_Encrypt(fileData, keyBytes);
        }
        else if (algorithm == "ChaCha20")
        {
            array<Byte>^ nonce = gcnew array<Byte>(12);
            Array::Copy(ivBytes, nonce, 12);
            encryptedData = ChaCha20_Encrypt(fileData, keyBytes, nonce);
        }
        else if (algorithm == "3DES")
        {
            encryptedData = TripleDES_Encrypt(fileData, keyBytes, ivBytes);
        }
        else if (algorithm == "Blowfish")
        {
            encryptedData = Blowfish_Encrypt(fileData, keyBytes, ivBytes);
        }
        else
        {
            return false;
        }

        File::WriteAllBytes(outputFile, encryptedData);
        return true;
    }
    catch (Exception^)
    {
        return false;
    }
}

bool MainForm::DecryptFile(String^ inputFile, String^ outputFile, String^ algorithm)
{
    try
    {
        array<Byte>^ fileData = File::ReadAllBytes(inputFile);
        array<Byte>^ keyBytes = Convert::FromBase64String(key);
        array<Byte>^ ivBytes = Convert::FromBase64String(iv);
        array<Byte>^ decryptedData;

        if (algorithm == "AES")
        {
            decryptedData = AES_Decrypt(fileData, keyBytes, ivBytes);
        }
        else if (algorithm == "RC4")
        {
            decryptedData = RC4_Decrypt(fileData, keyBytes);
        }
        else if (algorithm == "ChaCha20")
        {
            array<Byte>^ nonce = gcnew array<Byte>(12);
            Array::Copy(ivBytes, nonce, 12);
            decryptedData = ChaCha20_Decrypt(fileData, keyBytes, nonce);
        }
        else if (algorithm == "3DES")
        {
            decryptedData = TripleDES_Decrypt(fileData, keyBytes, ivBytes);
        }
        else if (algorithm == "Blowfish")
        {
            decryptedData = Blowfish_Decrypt(fileData, keyBytes, ivBytes);
        }
        else
        {
            return false;
        }

        File::WriteAllBytes(outputFile, decryptedData);
        return true;
    }
    catch (Exception^)
    {
        return false;
    }
}

// Algorithm Implementations
array<Byte>^ MainForm::AES_Encrypt(array<Byte>^ data, array<Byte>^ key, array<Byte>^ iv)
{
    Aes^ aes = Aes::Create();
    aes->Key = key;
    aes->IV = iv;
    aes->Mode = CipherMode::CBC;
    aes->Padding = PaddingMode::PKCS7;

    ICryptoTransform^ encryptor = aes->CreateEncryptor(aes->Key, aes->IV);
    MemoryStream^ ms = gcnew MemoryStream();
    CryptoStream^ cs = gcnew CryptoStream(ms, encryptor, CryptoStreamMode::Write);

    cs->Write(data, 0, data->Length);
    cs->FlushFinalBlock();

    return ms->ToArray();
}

array<Byte>^ MainForm::AES_Decrypt(array<Byte>^ data, array<Byte>^ key, array<Byte>^ iv)
{
    Aes^ aes = Aes::Create();
    aes->Key = key;
    aes->IV = iv;
    aes->Mode = CipherMode::CBC;
    aes->Padding = PaddingMode::PKCS7;

    ICryptoTransform^ decryptor = aes->CreateDecryptor(aes->Key, aes->IV);
    MemoryStream^ ms = gcnew MemoryStream(data);
    CryptoStream^ cs = gcnew CryptoStream(ms, decryptor, CryptoStreamMode::Read);
    MemoryStream^ result = gcnew MemoryStream();

    array<Byte>^ buffer = gcnew array<Byte>(4096);
    int read;
    while ((read = cs->Read(buffer, 0, buffer->Length)) > 0)
    {
        result->Write(buffer, 0, read);
    }

    return result->ToArray();
}

array<Byte>^ MainForm::RC4_Encrypt(array<Byte>^ data, array<Byte>^ key)
{
    array<Byte>^ result = gcnew array<Byte>(data->Length);
    array<int>^ s = gcnew array<int>(256);

    for (int i = 0; i < 256; i++)
    {
        s[i] = i;
    }

    int j = 0;
    for (int i = 0; i < 256; i++)
    {
        j = (j + s[i] + key[i % key->Length]) % 256;
        int temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }

    int i_index = 0;
    j = 0;
    for (int k = 0; k < data->Length; k++)
    {
        i_index = (i_index + 1) % 256;
        j = (j + s[i_index]) % 256;

        int temp = s[i_index];
        s[i_index] = s[j];
        s[j] = temp;

        int t = (s[i_index] + s[j]) % 256;
        result[k] = data[k] ^ (Byte)s[t];
    }

    return result;
}

array<Byte>^ MainForm::RC4_Decrypt(array<Byte>^ data, array<Byte>^ key)
{
    return RC4_Encrypt(data, key);
}

UInt32 MainForm::RotateLeft(UInt32 value, int offset)
{
    return (value << offset) | (value >> (32 - offset));
}

void MainForm::QuarterRound(array<UInt32>^ state, int a, int b, int c, int d)
{
    state[a] += state[b]; state[d] = RotateLeft(state[d] ^ state[a], 16);
    state[c] += state[d]; state[b] = RotateLeft(state[b] ^ state[c], 12);
    state[a] += state[b]; state[d] = RotateLeft(state[d] ^ state[a], 8);
    state[c] += state[d]; state[b] = RotateLeft(state[b] ^ state[c], 7);
}

array<Byte>^ MainForm::ChaCha20_Encrypt(array<Byte>^ data, array<Byte>^ key, array<Byte>^ nonce)
{
    array<Byte>^ result = gcnew array<Byte>(data->Length);
    array<UInt32>^ state = gcnew array<UInt32>(16);

    state[0] = 0x61707865;
    state[1] = 0x3320646e;
    state[2] = 0x79622d32;
    state[3] = 0x6b206574;

    for (int i = 0; i < 8; i++)
    {
        state[4 + i] = BitConverter::ToUInt32(key, i * 4);
    }

    state[12] = 0;

    for (int i = 0; i < 3; i++)
    {
        state[13 + i] = BitConverter::ToUInt32(nonce, i * 4);
    }

    int blockCount = (data->Length + 63) / 64;
    for (int block = 0; block < blockCount; block++)
    {
        state[12] = (UInt32)block;
        array<UInt32>^ workingState = (array<UInt32>^)state->Clone();

        for (int round = 0; round < 10; round++)
        {
            QuarterRound(workingState, 0, 4, 8, 12);
            QuarterRound(workingState, 1, 5, 9, 13);
            QuarterRound(workingState, 2, 6, 10, 14);
            QuarterRound(workingState, 3, 7, 11, 15);

            QuarterRound(workingState, 0, 5, 10, 15);
            QuarterRound(workingState, 1, 6, 11, 12);
            QuarterRound(workingState, 2, 7, 8, 13);
            QuarterRound(workingState, 3, 4, 9, 14);
        }

        for (int i = 0; i < 16; i++)
        {
            workingState[i] += state[i];
        }

        array<Byte>^ keyStream = gcnew array<Byte>(64);
        for (int i = 0; i < 16; i++)
        {
            array<Byte>^ word = BitConverter::GetBytes(workingState[i]);
            Array::Copy(word, 0, keyStream, i * 4, 4);
        }

        int blockStart = block * 64;
        int blockSize = Math::Min(64, data->Length - blockStart);
        for (int i = 0; i < blockSize; i++)
        {
            result[blockStart + i] = (Byte)(data[blockStart + i] ^ keyStream[i]);
        }
    }

    return result;
}

array<Byte>^ MainForm::ChaCha20_Decrypt(array<Byte>^ data, array<Byte>^ key, array<Byte>^ nonce)
{
    return ChaCha20_Encrypt(data, key, nonce);
}

array<Byte>^ MainForm::TripleDES_Encrypt(array<Byte>^ data, array<Byte>^ key, array<Byte>^ iv)
{
    TripleDES^ tripleDes = TripleDES::Create();

    // Ensure key is proper size for 3DES
    array<Byte>^ properKey = gcnew array<Byte>(24);
    if (key->Length >= 24)
    {
        Array::Copy(key, properKey, 24);
    }
    else
    {
        // Pad key if necessary
        for (int i = 0; i < 24; i++)
        {
            properKey[i] = key[i % key->Length];
        }
    }

    tripleDes->Key = properKey;
    tripleDes->IV = iv;
    tripleDes->Mode = CipherMode::CBC;
    tripleDes->Padding = PaddingMode::PKCS7;

    ICryptoTransform^ encryptor = tripleDes->CreateEncryptor(tripleDes->Key, tripleDes->IV);
    MemoryStream^ ms = gcnew MemoryStream();
    CryptoStream^ cs = gcnew CryptoStream(ms, encryptor, CryptoStreamMode::Write);

    cs->Write(data, 0, data->Length);
    cs->FlushFinalBlock();

    return ms->ToArray();
}

array<Byte>^ MainForm::TripleDES_Decrypt(array<Byte>^ data, array<Byte>^ key, array<Byte>^ iv)
{
    TripleDES^ tripleDes = TripleDES::Create();

    array<Byte>^ properKey = gcnew array<Byte>(24);
    if (key->Length >= 24)
    {
        Array::Copy(key, properKey, 24);
    }
    else
    {
        for (int i = 0; i < 24; i++)
        {
            properKey[i] = key[i % key->Length];
        }
    }

    tripleDes->Key = properKey;
    tripleDes->IV = iv;
    tripleDes->Mode = CipherMode::CBC;
    tripleDes->Padding = PaddingMode::PKCS7;

    ICryptoTransform^ decryptor = tripleDes->CreateDecryptor(tripleDes->Key, tripleDes->IV);
    MemoryStream^ ms = gcnew MemoryStream(data);
    CryptoStream^ cs = gcnew CryptoStream(ms, decryptor, CryptoStreamMode::Read);
    MemoryStream^ result = gcnew MemoryStream();

    array<Byte>^ buffer = gcnew array<Byte>(4096);
    int read;
    while ((read = cs->Read(buffer, 0, buffer->Length)) > 0)
    {
        result->Write(buffer, 0, read);
    }

    return result->ToArray();
}

array<Byte>^ MainForm::Blowfish_Encrypt(array<Byte>^ data, array<Byte>^ key, array<Byte>^ iv)
{
    array<Byte>^ result = gcnew array<Byte>(data->Length);
    array<Byte>^ previousBlock = (array<Byte>^)iv->Clone();

    for (int i = 0; i < data->Length; i += 8)
    {
        int blockSize = Math::Min(8, data->Length - i);
        array<Byte>^ block = gcnew array<Byte>(8);
        Array::Copy(data, i, block, 0, blockSize);

        for (int j = 0; j < blockSize; j++)
        {
            block[j] ^= previousBlock[j];
        }

        for (int round = 0; round < 16; round++)
        {
            for (int j = 0; j < blockSize; j++)
            {
                block[j] = (Byte)(block[j] ^ key[(round + j) % key->Length]);
            }
        }

        Array::Copy(block, 0, result, i, blockSize);
        previousBlock = block;
    }

    return result;
}

array<Byte>^ MainForm::Blowfish_Decrypt(array<Byte>^ data, array<Byte>^ key, array<Byte>^ iv)
{
    array<Byte>^ result = gcnew array<Byte>(data->Length);
    array<Byte>^ previousBlock = (array<Byte>^)iv->Clone();

    for (int i = 0; i < data->Length; i += 8)
    {
        int blockSize = Math::Min(8, data->Length - i);
        array<Byte>^ block = gcnew array<Byte>(8);
        Array::Copy(data, i, block, 0, blockSize);

        array<Byte>^ tempBlock = (array<Byte>^)block->Clone();

        for (int round = 15; round >= 0; round--)
        {
            for (int j = 0; j < blockSize; j++)
            {
                block[j] = (Byte)(block[j] ^ key[(round + j) % key->Length]);
            }
        }

        for (int j = 0; j < blockSize; j++)
        {
            block[j] ^= previousBlock[j];
            result[i + j] = block[j];
        }

        previousBlock = tempBlock;
    }

    return result;
}